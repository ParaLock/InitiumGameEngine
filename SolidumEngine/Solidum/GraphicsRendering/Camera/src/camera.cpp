#include "../include/camera.h"

camera::camera(float near_value, float far_value):
	dV(D3DXVECTOR3(0, 0, 1)),
	dU(D3DXVECTOR3(0, 1, 0)),
	eye(D3DXVECTOR3(0, 0, 0)),
	view(D3DXVECTOR3(0, 0, 1)),
	up(D3DXVECTOR3(0, 1, 0)),
	forward(D3DXVECTOR3(0, 0, 1)),
	strafeRight(D3DXVECTOR3(1, 0, 0)),
	heading(0),
	pitch(0)
{

	movementToggles[0] = 0;
	movementToggles[1] = 0;
	movementToggles[2] = 0;
	movementToggles[3] = 0;

	lockMouse = true;

	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProjection);
	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixPerspectiveFovLH(&matProjection,
		(FLOAT)D3DXToRadian(45),
		(FLOAT)windowAccessor::screen_width / (FLOAT)windowAccessor::screen_height,
		near_value,
		far_value);

	mouseOldPosX = 0;
	mouseOldPosY = 0;

	D3DXMatrixOrthoLH(&orthoMatrix, (float)windowAccessor::screen_width, (float)windowAccessor::screen_height, near_value, far_value);

	setCamStartView();

}

camera::~camera()
{
}

void camera::setCamStartView()
{
	D3DXMatrixRotationYawPitchRoll(&matRotate, heading, pitch, 0);

	D3DXVec3TransformCoord(&view, &dV, &matRotate);
	D3DXVec3TransformCoord(&up, &dU, &matRotate);

	D3DXVec3Normalize(&forward, &view);
	D3DXVec3Cross(&strafeRight, &up, &view);
	D3DXVec3Normalize(&strafeRight, &strafeRight);

	view = eye + view;

	D3DXMatrixLookAtLH(&matView, &eye, &view, &up);

	this->startCamView = matView;
}

float toRadians(float input) {
	float halfC = M_PI / 180;
	return input * halfC;
}

void camera::setPositionAndView(float x, float y, float z, float hDeg, float pDeg)
{
	eye.x = x;
	eye.y = y;
	eye.z = z;

	heading = hDeg * (float)DEG_TO_RAD;
	pitch = pDeg * (float)DEG_TO_RAD;

	UpdateView();
}

void camera::adjustHeadingPitch(float hRad, float pRad)
{
	heading += hRad;
	pitch += pRad;

	if (heading > TWO_PI) heading -= (float)TWO_PI;
	else if (heading < 0) heading = (float)TWO_PI + heading;

	if (pitch > TWO_PI) pitch -= (float)TWO_PI;
	else if (pitch < 0) pitch = (float)TWO_PI + pitch;

}

void camera::cameraMove(std::string direction, float speed)
{
	if (direction == "right")
		movementToggles[3] += speed;

	if (direction == "left")
		movementToggles[2] -= speed;

	if (direction == "forward") {
		movementToggles[0] += speed;
	}

	if (direction == "backward") {
		movementToggles[1] -= speed;
	}
	if (direction == "lookup") {
		adjustHeadingPitch(0.0f, speed * -1.0f);
	}
	if (direction == "lookdown") {
	    adjustHeadingPitch(0.0f, speed * 1.0f);
	}
	if (direction == "lookright") {
		adjustHeadingPitch(speed * -1.0f, 0.0f);
	}
	if (direction == "lookleft") {
		adjustHeadingPitch(speed * 1.0f, 0.0f);
	}

}

int appLaunchMouseDebounceCount = 0;

void camera::cameraMouseLook()
{
	GetCursorPos(&mousePos);

	if (lockMouse != true) {
		ShowCursor(true);
	}
	else {
		ShowCursor(false);
	

	SetFocus(windowAccessor::hWnd);

	if (ScreenToClient(windowAccessor::hWnd, &mousePos))
	{
		if (appLaunchMouseDebounceCount > 20) {

			mouseMoveDiff = 0.0f;

			if (mouseOldPosX > mousePos.x) {
				mouseMoveDiff = ((mouseOldPosX - mousePos.x) / 90);

				if (mouseOldPosX - mousePos.x > 30)
					mouseMoveDiff = 0.0f;

				if (mouseMoveDiff < 0) {
					mouseMoveDiff = 0.0f;
				}
				cameraMove("lookright", mouseMoveDiff);
			}

			if (mouseOldPosX < mousePos.x) {
				mouseMoveDiff = ((mousePos.x - mouseOldPosX) / 90);


				if (mousePos.x - mouseOldPosX > 30)
					mouseMoveDiff = 0.0f;

				if (mouseMoveDiff < 0) {
					mouseMoveDiff = 0.0f;
				}
				cameraMove("lookleft", mouseMoveDiff);
			}

			if (mouseOldPosY > mousePos.y) {
				mouseMoveDiff = ((mouseOldPosY - mousePos.y) / 90);

				if (mouseOldPosY - mousePos.y > 30)
					mouseMoveDiff = 0.0f;

				if (mouseMoveDiff < 0) {
					mouseMoveDiff = 0.0f;
				}
				cameraMove("lookup", mouseMoveDiff);
			}

			if (mouseOldPosY < mousePos.y) {
				mouseMoveDiff = ((mousePos.y - mouseOldPosY) / 90);

				if (mousePos.y - mouseOldPosY > 30)
					mouseMoveDiff = 0.0f;

				if (mouseMoveDiff < 0) {
					mouseMoveDiff = 0.0f;
				}
				cameraMove("lookdown", mouseMoveDiff);
			}
		}
		appLaunchMouseDebounceCount++;

	}
		if (lockMouse == true) {

			if (mousePos.x < 0)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

			if (mousePos.x >= windowAccessor::screen_width)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

			if (mousePos.y < 0)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

			if (mousePos.y >= windowAccessor::screen_height)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

			if (mousePos.x == 0 && mousePos.y == 0)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

			if (mousePos.y >= windowAccessor::screen_height&& mousePos.x >= windowAccessor::screen_width)
				SetCursorPos((windowAccessor::screen_width / 2) + 300, (windowAccessor::screen_height / 2) + 300);

		}

		mouseOldPosX = mousePos.x;
		mouseOldPosY = mousePos.y;
	}
}

void camera::Update()
{
	float t = (float)camTimer.getElapsedTimeSeconds();

	eye += t * (movementToggles[0] + movementToggles[1]) * 1.5f * forward +
		t * (movementToggles[2] + movementToggles[3]) * 1.5f * strafeRight;

	UpdateView();

	camTimer.reset();

	movementToggles[0] = 0;
	movementToggles[1] = 0;
	movementToggles[2] = 0;
	movementToggles[3] = 0;
}


void camera::UpdateView()
{
	D3DXMatrixRotationYawPitchRoll(&matRotate, heading, pitch, 0);

	D3DXVec3TransformCoord(&view, &dV, &matRotate);
	D3DXVec3TransformCoord(&up, &dU, &matRotate);

	D3DXVec3Normalize(&forward, &view);
	D3DXVec3Cross(&strafeRight, &up, &view);
	D3DXVec3Normalize(&strafeRight, &strafeRight);

	view = eye + view;

	D3DXMatrixLookAtLH(&matView, &eye, &view, &up);

}

