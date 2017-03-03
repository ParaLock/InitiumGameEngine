#include "../include/MoveComponent.h"


MoveComponent::MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl, KEY_FUNCTION_MAP* keyMap)
{
	setType(COMPONENT_TYPE::MOVE_COMPONENT);

	if (keyboardControl) {
		EventFrameworkCore::getInstance()->
			getGlobalEventHub("InputEventHub")->subscribeListener(this);
	}

	_vPos = startPos;
	_movementSpeed = movementSpeed;

	_keyFuncMap = keyMap;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update()
{
	if (_parent->getParent() != nullptr) {

		Vector3f finalPos = _vPos + _parent->getParent()->getTransform()->getPos();

		_parent->getTransform()->setPos(finalPos);

	}
	else {
		_parent->getTransform()->setPos(_vPos);
	}
}

void MoveComponent::onEvent(EVENT_PTR evt)
{
	switch (evt.get()->getEvent<InputEvent>()->getType())
	{
	case EVENT_TYPE::INPUT_EVENT: {
		auto mousePos = evt.get()->getEvent<InputEvent>()->getMousePos();
		auto keysPressed = evt.get()->getEvent<InputEvent>()->getPressedKeys();

		for (auto itr = keysPressed.begin(); itr != keysPressed.end(); itr++) {
			auto keyfuncItr = _keyFuncMap->find(*itr);

			if (keyfuncItr != _keyFuncMap->end()) {

				switch (_keyFuncMap->at(*itr)) {
				case MOVE_FUNCTION::MOVE_BACKWARD:
					_vPos[2] -= _movementSpeed;
					break;
				case MOVE_FUNCTION::MOVE_FORWARD:
					_vPos[2] += _movementSpeed;
					break;
				case MOVE_FUNCTION::MOVE_DOWN:
					_vPos[1] -= _movementSpeed;
					break;
				case MOVE_FUNCTION::MOVE_UP:
					_vPos[1] += _movementSpeed;
					break;
				case MOVE_FUNCTION::MOVE_LEFT:
					_vPos[0] += _movementSpeed;
					break;
				case MOVE_FUNCTION::MOVE_RIGHT:
					_vPos[0] -= _movementSpeed;
					break;
				default:
					break;
				}

			}			
		}
		break;
	}
	default:
		break;
	}
}
