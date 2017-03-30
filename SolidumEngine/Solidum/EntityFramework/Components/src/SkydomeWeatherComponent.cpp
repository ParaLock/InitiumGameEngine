#include "../include/SkydomeWeatherComponent.h"



SkydomeWeatherComponent::SkydomeWeatherComponent(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor, int index)
{
	_index = index;

	_weatherApexColor = apexColor;
	_weatherCenterColor = centerColor;

	_shader = shader;
	_tex = tex;
	_cam = cam;
	_index = index;
	_skydome = skydome;

	setType(COMPONENT_TYPE::SKYBOX_WEATHER_COMPONENT);
}


SkydomeWeatherComponent::~SkydomeWeatherComponent()
{
}

void SkydomeWeatherComponent::init()
{
	uint64_t nodeID = GraphicsCore::getInstance()->getRenderNodeTree()->getUniqueNodeID();

	_parent->getRenderObject()->addGenericRenderNode(new
		SkyBoxRenderNode(_shader, _tex, _skydome, _cam, _weatherApexColor, _weatherCenterColor, nodeID),
		RENDER_NODE_TYPE::SKYBOX_WEATHER_RENDER_NODE, _index);
}

void SkydomeWeatherComponent::update(float delta)
{
	updateDayNightCycle(0.0005f);

	RenderParams params;

	params.setPerNodeParam_skydomeApexColor(_weatherApexColor);
	params.setPerNodeParam_skydomeCenterColor(_weatherCenterColor);

	if (_parent != nullptr)
		_parent->getRenderObject()->updateRenderNode(RENDER_NODE_TYPE::SKYBOX_WEATHER_RENDER_NODE, _index, params);
}

void SkydomeWeatherComponent::updateDayNightCycle(float delta)
{
	if (CURRENT_TIME > _skyCycle[_timeOfDayIndex].INTERVAL) {
		CURRENT_TIME = 0.0f;
		_timeOfDayIndex++;
	}

	switch (_skyCycle[_timeOfDayIndex].STATE) {
	case TIME_OF_DAY_CYCLE::MID_DAY:

		if (_weatherApexColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] += 0.0001f;
		if (_weatherApexColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] += 0.0001f;
		if (_weatherApexColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] += 0.0001f;

		if (_weatherCenterColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] += 0.0001f;
		if (_weatherCenterColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] += 0.0001f;
		if (_weatherCenterColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] += 0.0001f;

		if (_weatherApexColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] -= 0.0001f;
		if (_weatherApexColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] -= 0.0001f;
		if (_weatherApexColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] -= 0.0001f;

		if (_weatherCenterColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] -= 0.0001f;
		if (_weatherCenterColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] -= 0.0001f;
		if (_weatherCenterColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] -= 0.0001f;

		break;
	case TIME_OF_DAY_CYCLE::SUN_RISE:

		if (_weatherApexColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] += 0.0001f;
		if (_weatherApexColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] += 0.0001f;
		if (_weatherApexColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] += 0.0001f;

		if (_weatherCenterColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] += 0.0001f;
		if (_weatherCenterColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] += 0.0001f;
		if (_weatherCenterColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] += 0.0001f;

		if (_weatherApexColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] -= 0.0001f;
		if (_weatherApexColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] -= 0.0001f;
		if (_weatherApexColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] -= 0.0001f;

		if (_weatherCenterColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] -= 0.0001f;
		if (_weatherCenterColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] -= 0.0001f;
		if (_weatherCenterColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] -= 0.0001f;



		break;
	case TIME_OF_DAY_CYCLE::SUN_SET:

		if (_weatherApexColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] += 0.0001f;
		if (_weatherApexColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] += 0.0001f;
		if (_weatherApexColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] += 0.0001f;

		if (_weatherCenterColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] += 0.0001f;
		if (_weatherCenterColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] += 0.0001f;
		if (_weatherCenterColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] += 0.0001f;

		if (_weatherApexColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] -= 0.0001f;
		if (_weatherApexColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] -= 0.0001f;
		if (_weatherApexColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] -= 0.0001f;

		if (_weatherCenterColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] -= 0.0001f;
		if (_weatherCenterColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] -= 0.0001f;
		if (_weatherCenterColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] -= 0.0001f;



		break;
	case TIME_OF_DAY_CYCLE::NIGHT:

		if (_weatherApexColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] += 0.0001f;
		if (_weatherApexColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] += 0.0001f;
		if (_weatherApexColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] += 0.0001f;

		if (_weatherCenterColor[0] < _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] += 0.0001f;
		if (_weatherCenterColor[1] < _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] += 0.0001f;
		if (_weatherCenterColor[2] < _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] += 0.0001f;

		if (_weatherApexColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[0])
			_weatherApexColor[0] -= 0.00015f;
		if (_weatherApexColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[1])
			_weatherApexColor[1] -= 0.0001f;
		if (_weatherApexColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_apex[2])
			_weatherApexColor[2] -= 0.0001f;

		if (_weatherCenterColor[0] > _skyCycle[_timeOfDayIndex].goal_rgb_center[0])
			_weatherCenterColor[0] -= 0.0001f;
		if (_weatherCenterColor[1] > _skyCycle[_timeOfDayIndex].goal_rgb_center[1])
			_weatherCenterColor[1] -= 0.0001f;
		if (_weatherCenterColor[2] > _skyCycle[_timeOfDayIndex].goal_rgb_center[2])
			_weatherCenterColor[2] -= 0.0001f;

		break;
	}

	_timeOfDayIndex = _timeOfDayIndex % 4;

	CURRENT_TIME += delta;


}

void SkydomeWeatherComponent::onEvent(EVENT_PTR evt)
{
}
