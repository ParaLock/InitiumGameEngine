#pragma once

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "../../../GraphicsRendering/Lights/include/Light.h"

#include "Component.h"

class RenderDataPacket;

class SunMoonLightingComponent : public Component
{
private:
	float lightAngle = 0.0f;

	uint64_t _renderNodeID[2];

	Light* _sun;
	Light* _moon;

	float _speed = 0.0f;

	float _previousDelta;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };
public:
	SunMoonLightingComponent(Light* sun, Light* moon, float speed, IEntity* entity);
	~SunMoonLightingComponent();

	void init() {};

	void update(float delta);

	void onEvent(EVENT_PTR evt) {};

	void AddRenderData(RenderDataGroup* collection) {};
};

