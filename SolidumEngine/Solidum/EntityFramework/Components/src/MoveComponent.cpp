#include "../include/MoveComponent.h"


MoveComponent::MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl)
{
	_type = COMPONENT_TYPE::MOVE_COMPONENT;

	if (keyboardControl) {
		EventFrameworkCore::getInstance()->
			getGlobalEventHub("InputEventHub")->subscribeListener(this);
	}

	_vPos = startPos;
	_movementSpeed = movementSpeed;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update()
{
	if (_parent != nullptr) {

		_parent->getTransform()->setPos(_vPos);
	}
}

void MoveComponent::onEvent(IEvent * evt)
{

	switch (evt->getType())
	{
	case EVENT_TYPE::INPUT_EVENT: {
		auto mousePos = evt->getEvent<InputEvent>()->getMousePos();
		auto keysPressed = evt->getEvent<InputEvent>()->getPressedKeys();

		for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
			switch (*itr) {
			case KEY_MAP::UP:
				_vPos._y += _movementSpeed;
				break;
			case KEY_MAP::DOWN:
				_vPos._y -= _movementSpeed;
				break;
			case KEY_MAP::LEFT:
				_vPos._x += _movementSpeed;
				break;
			case KEY_MAP::RIGHT:
				_vPos._x -= _movementSpeed;
				break;
			}
		}
		break;
	}
	default:
		break;
	}
}