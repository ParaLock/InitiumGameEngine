#include "../include/SkydomeWeatherComponent.h"



SkydomeWeatherComponent::SkydomeWeatherComponent(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor)
{
	_weatherApexColor = apexColor;
	_weatherCenterColor = centerColor;

	_renderNodeID = GraphicsCore::getInstance()->getInstance()->getRenderNodeTree()->getUniqueNodeID();

	GraphicsCore::getInstance()->getRenderNodeTree()->addNode(new 
		SkyBoxRenderNode(shader, tex, skydome, cam, apexColor, centerColor), _renderNodeID);

	setType(COMPONENT_TYPE::SKYBOX_WEATHER_COMPONENT);
}


SkydomeWeatherComponent::~SkydomeWeatherComponent()
{
}

void SkydomeWeatherComponent::update(float delta)
{
	updateDayNightCycle(0.0005f);

	LocalRenderingParams params;

	params._skydomeApexColor = _weatherApexColor;
	params._skydomeCenterColor = _weatherCenterColor;

	GraphicsCore::getInstance()->getRenderNodeTree()->updateNodeLocalRenderParams(params, _renderNodeID);
}

void SkydomeWeatherComponent::updateDayNightCycle(float delta)
{
	if (CURRENT_TIME > _skyCycle[_timeOfDayIndex].INTERVAL) {
		CURRENT_TIME = 0.0f;
		_timeOfDayIndex++;
	}

	switch (_skyCycle[_timeOfDayIndex].STATE) {
	case TIME_OF_DAY_CYCLE::MID_DAY:

		std::cout << "MID_DAY" << std::endl;

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
		std::cout << "SUN_RISE" << std::endl;

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
		std::cout << "SUN_SET" << std::endl;

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
		std::cout << "NIGHT" << std::endl;

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
