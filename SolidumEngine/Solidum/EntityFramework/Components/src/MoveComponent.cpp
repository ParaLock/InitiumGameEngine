#include "../include/MoveComponent.h"


MoveComponent::MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl, KEY_FUNCTION_MAP* keyMap, IEntity* entity)
{
	setType(COMPONENT_TYPE::MOVE_COMPONENT);

	if (keyboardControl) {
		EventFrameworkCore::getInstance()->
			getGlobalEventHub("InputEventHub")->subscribeListener(this);
	}

	_vPos = startPos;
	_movementSpeed = movementSpeed;

	_keyFuncMap = keyMap;

	_parent = entity;
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::update(float delta)
{
	Vector3f diff = Vector3f(0,0,0);

	if (_parent->getParent()) {
		diff = Matrix4f::getPos(_parent->getParent()->getTransform()->getGlobalTransform());
	}

	_parent->getTransform()->setPosition(_vPos + diff);
}

void MoveComponent::onEvent(EVENT_PTR evt)
{
	switch (evt.get()->getType())
	{
	case EVENT_TYPE::INPUT_EVENT: {


		InputEvtData* evtData = (InputEvtData*)evt.get()->getData().get();

		auto mousePos = evtData->getMousePos();
		auto keysPressed = evtData->getPressedKeys();

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
