#pragma once
#include "../../../EventFramework/include/IEvent.h"
#include "../../../EventFramework/include/InputEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2f.h"
#include "../../../EngineUtils/include/Vector3f.h"

#include "Component.h"

class MoveComponent : public Component
{
private:
	Vector3f _vPos;

	float _movementSpeed = 0.0f;
protected:

public:
	MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl);
	~MoveComponent();

	void update();

	void onEvent(IEvent* evt);
};

