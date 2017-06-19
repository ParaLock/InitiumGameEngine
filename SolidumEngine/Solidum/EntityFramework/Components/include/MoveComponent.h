#pragma once
#include "../../../EventFramework/include/Event.h"

#include "../../../InputHandling/include/InputHandler.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "Component.h"

class RenderDataPacket;

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

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };
protected:

public:
	MoveComponent(Vector3f startPos, float movementSpeed, bool keyboardControl, KEY_FUNCTION_MAP* keyMap, IEntity* entity);
	~MoveComponent();

	void update(float delta);

	void onEvent(EVENT_PTR evt);

	void AddRenderData(RenderDataGroup* collection) {};
};

