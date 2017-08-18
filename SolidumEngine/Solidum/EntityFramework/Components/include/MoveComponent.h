#pragma once
#include "../../../EventFramework/include/Event.h"

#include "../../../InputHandling/include/InputHandler.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../../SolidumAPI/common.h"

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

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {};
	void unload() {};
public:
	MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl, KEY_FUNCTION_MAP* keyMap, IEntity* entity);
	~MoveComponent();

	struct InitData : public ResourceInitParams {
		InitData() {}

		
	};

	void update(float delta);

	void onEvent(EVENT_PTR evt);

	void AddRenderData(RenderDataGroup* collection) {};
protected:

};

