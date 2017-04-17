#include "../include/CameraComponent.h"

CameraComponent::CameraComponent(float near_value, float far_value, IEntity* entity) :
	_dV(Vector3f(0, 0, 1)),
	_dU(Vector3f(0, 1, 0)),
	_up(Vector3f(0, 1, 0)),
	_forward(Vector3f(0, 0, 1)),
	_view(Vector3f(0, 0, 1)),
	_eye(Vector3f(0, 0, 0)),
	_strafeRight(Vector3f(1, 0, 0)),
	_yaw(0),
	_pitch(0)
{
	setType(COMPONENT_TYPE::CAMERA_COMPONENT);

	_parent = entity;

	EventFrameworkCore::getInstance()->getGlobalEventHub("InputEventHub")->subscribeListener(this);

	_viewMatrix = Matrix4f::get_identity();
	_projectionMatrix = Matrix4f::get_identity();
	_worldMatrix = Matrix4f::get_identity();
	_matTranslation = Matrix4f::get_identity();
	_matModelMatrix = Matrix4f::get_identity();

	float aspect = (float)window::getInstance()->screen_width / (float)window::getInstance()->screen_height;
	
	screen_width = (float)window::getInstance()->screen_width;
	screen_height = (float)window::getInstance()->screen_height;

	float left, right, top, bottom;

	_projectionMatrix = Matrix4f::get_perspectiveRH(45, aspect, near_value, far_value);

	left = (float)((screen_width / 2) * -1);
	right = left + (float)screen_width;
	top = (float)(screen_height / 2);
	bottom = top - (float)screen_height;

	_orthoProjectionMatrix = Matrix4f::get_orthographicRH(left, right, bottom, top, near_value, far_value);

	_movementStore[0] = 0;
	_movementStore[1] = 0;
	_movementStore[2] = 0;
	_movementStore[3] = 0;

	_startViewMatrix = _viewMatrix;

	_screenCenter[0] = (screen_width / 2);
	_screenCenter[1] = (screen_height / 2);

	_previousMousePos = Vector2f(_screenCenter[0], _screenCenter[1]);

	POINT pt = { (LONG)_screenCenter[0], (LONG)_screenCenter[1] };
	ClientToScreen(window::getInstance()->hWnd, &pt);
	SetCursorPos(pt.x, pt.y);

	_mouseLocked = false;

	ShowCursor(false);

	isLoaded = true;
}

CameraComponent::~CameraComponent()
{
	isLoaded = false;
}

float toRadians(float input) {
	float halfC = M_PI / 180;
	return input * halfC;
}

void CameraComponent::onEvent(EVENT_PTR evt)
{
	switch (evt.get()->getType())
	{

		case EVENT_TYPE::INPUT_EVENT: {
			auto mousePos = evt.get()->getEvent<InputEvent>()->getMousePos();
			auto keysPressed = evt.get()->getEvent<InputEvent>()->getPressedKeys();

			updateLook((float)mousePos.first, (float)mousePos.second);

			for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
				switch (*itr) {
				case KEY_MAP::W:
					move(CAMERA_MOVE::CAM_FORWARD, 5.0f);
					break;
				case KEY_MAP::A:
					move(CAMERA_MOVE::CAM_LEFT, 5.0f);
					break;
				case KEY_MAP::S:
					move(CAMERA_MOVE::CAM_BACKWARD, 5.0f);
					break;
				case KEY_MAP::D:
					move(CAMERA_MOVE::CAM_RIGHT, 5.0f);
					break;
				}
			}
			break;
		}
		default:
			break;
	}
}

void CameraComponent::adjustYawAndPitch(float yaw, float pitch)
{
	_yaw += yaw;
	_pitch += pitch;

	if (_yaw > TWO_PI) _yaw -= (float)TWO_PI;
	else if (_yaw < 0) _yaw = (float)TWO_PI + _yaw;

	if (_pitch > TWO_PI) _pitch -= (float)TWO_PI;
	else if (_pitch < 0) _pitch = (float)TWO_PI + _pitch;
}

void CameraComponent::updateLook(float mouseX, float mouseY)
{
	float mX = mouseX;
	float mY = mouseY;

	static float mouseDiff = 0.0f;
	
	bool mousePosReset = false;

	if (_mouseLocked == true) {

		if (mX < 0) 
			mousePosReset = true;

		if (mX >= screen_width) 
			mousePosReset = true;

		if (mY < 0) 
			mousePosReset = true;

		if (mY >= screen_height) 
			mousePosReset = true;

		if (mX == 0 && mY == 0) 
			mousePosReset = true;	

		if (mY >= screen_height && mX >= screen_width) 
			mousePosReset = true;
		

		if (mousePosReset) {

			_previousMousePos = Vector2f(_screenCenter[0], _screenCenter[1]);

			POINT pt = { (LONG)_screenCenter[0], (LONG)_screenCenter[1] };
			ClientToScreen(window::getInstance()->hWnd, &pt);
			SetCursorPos(pt.x, pt.y);

			return;
		}
	}

	if (_previousMousePos.getX() > mX) {

		mouseDiff = (_previousMousePos.getX() - mX) / SMOOTHING_FACTOR;

		move(CAMERA_MOVE::CAM_LOOK_RIGHT, mouseDiff);
	}

	if (_previousMousePos.getX() < mX) {

		mouseDiff = (mX - _previousMousePos.getX()) / SMOOTHING_FACTOR;

		move(CAMERA_MOVE::CAM_LOOK_LEFT, mouseDiff);
	}

	if (_previousMousePos.getY() > mY) {

		mouseDiff = (_previousMousePos.getY() - mY) / SMOOTHING_FACTOR;

		move(CAMERA_MOVE::CAM_LOOK_UP, mouseDiff);
	}

	if (_previousMousePos.getY() < mY) {

		mouseDiff = (mY - _previousMousePos.getY()) / SMOOTHING_FACTOR;

		move(CAMERA_MOVE::CAM_LOOK_DOWN, mouseDiff);
	}


	_previousMousePos[0] = mX;
	_previousMousePos[1] = mY;
}

void CameraComponent::move(CAMERA_MOVE direction, float speed)
{
	if (speed > 5 || speed < -1)
		return;

	switch (direction) {
	case CAMERA_MOVE::CAM_LOOK_DOWN:
		adjustYawAndPitch(0.0f, speed * 1.0f);
		break;
	case CAMERA_MOVE::CAM_LOOK_UP:
		adjustYawAndPitch(0.0f, speed * -1.0f);
		break;
	case CAMERA_MOVE::CAM_LOOK_LEFT:
		adjustYawAndPitch(speed * 1.0f, 0.0f);
		break;
	case CAMERA_MOVE::CAM_LOOK_RIGHT:
		adjustYawAndPitch(speed * -1.0f, 0.0f);
		break;

	case CAMERA_MOVE::CAM_FORWARD:
		_movementStore[0] += speed;
		break;
	case CAMERA_MOVE::CAM_BACKWARD:
		_movementStore[1] -= speed;
		break;
	case CAMERA_MOVE::CAM_LEFT:
		_movementStore[2] -= speed;
		break;
	case CAMERA_MOVE::CAM_RIGHT:
		_movementStore[3] += speed;
		break;
	}
}

void CameraComponent::update(float delta)
{
	float t = (float)camTimer.getElapsedTimeSeconds();

	_eye += _forward * t * (_movementStore[0] + _movementStore[1]) * 1.5f +
		_strafeRight * t * (_movementStore[2] + _movementStore[3]) * 1.5f;

	_matRotate = Matrix4f::get_rot_of_YawPitchRoll(0, _pitch, _yaw);
	_view = Matrix4f::transform(_dV, _matRotate);
	_up = Matrix4f::transform(_dU, _matRotate);

	_forward = Vector3f::normalize(_view);

	_strafeRight = Vector3f::normalize(Vector3f::cross_product(_up, _view));

	_view = _eye + _view;

	_viewMatrix = Matrix4f::get_lookAtLH(_eye, _view, _up);

	camTimer.reset();

	_movementStore[0] = 0;
	_movementStore[1] = 0;
	_movementStore[2] = 0;
	_movementStore[3] = 0;
}

