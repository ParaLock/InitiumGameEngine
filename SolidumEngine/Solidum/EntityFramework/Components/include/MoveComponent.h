#pragma once
#include "../../../EventFramework/include/IEvent.h"
#include "../../../EventFramework/include/InputEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2f.h"
#include "../../../EngineUtils/include/Vector3f.h"

#include "Component.h"

enum MOVE_FUNCTION {
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN
};

typedef std::map<KEY_MAP, MOVE_FUNCTION> KEY_FUNCTION_MAP;

class MoveComponent : public Component
{
private:
	Vector3f _vPos;

	float _movementSpeed = 0.0f;

	KEY_FUNCTION_MAP* _keyFuncMap;
protected:

public:
	MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl, KEY_FUNCTION_MAP* keyMap);
	~MoveComponent();

	void update();

	void onEvent(IEvent* evt);
};

