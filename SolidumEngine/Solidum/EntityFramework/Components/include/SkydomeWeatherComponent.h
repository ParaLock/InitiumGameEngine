#pragma once
#include "../../../EventFramework/include/IEvent.h"
#include "../../../EventFramework/include/InputEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "../../../GraphicsRendering/RenderNode/include/SkyBoxRenderNode.h"

#include "Component.h"

enum class TIME_OF_DAY_CYCLE {
	SUN_RISE,
	MID_DAY,
	SUN_SET,
	NIGHT,
};

struct TIME_OF_DAY_BLOCK {
	float INTERVAL;
	TIME_OF_DAY_CYCLE STATE;
	float goal_rgb_apex[3];
	float goal_rgb_center[3];
	//float change_speed;
};

class SkydomeWeatherComponent : public Component
{
private:
	uint64_t _renderNodeID;

	Vector4f _weatherCenterColor;
	Vector4f _weatherApexColor;

	float CURRENT_TIME = 0.0f;

	int _timeOfDayIndex = 0;

	TIME_OF_DAY_BLOCK _skyCycle[4] =
	{ { 2.7f, TIME_OF_DAY_CYCLE::MID_DAY, 1.0f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f },
	{ 0.6f, TIME_OF_DAY_CYCLE::SUN_SET, 0.5f, 0.06f, 0.06f, 0.06f, 0.06f, 0.06f },
	{ 4.0f, TIME_OF_DAY_CYCLE::NIGHT, 0.04f, 0.04f, 0.1f, 0.04f, 0.04f, 0.1f } };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(IResourceBuilder* builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

public:
	SkydomeWeatherComponent(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor);
	~SkydomeWeatherComponent();

	void update();

	void onEvent(EVENT_PTR evt);

	void updateDayNightCycle(float delta);
};

