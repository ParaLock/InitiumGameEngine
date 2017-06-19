#include "../include/SkydomeWeatherComponent.h"



SkydomeWeatherComponent::SkydomeWeatherComponent(Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor, int index, IEntity* entity)
{
	_index = index;

	_weatherApexColor = apexColor;
	_weatherCenterColor = centerColor;

	_tex = tex;
	_cam = cam;
	_index = index;
	_skydome = skydome;

	setType(COMPONENT_TYPE::SKYBOX_WEATHER_COMPONENT);

	_parent = entity;

	_parent->getRenderObject()->addUniqueComponent(this);
}


SkydomeWeatherComponent::~SkydomeWeatherComponent()
{
}

void SkydomeWeatherComponent::update(float delta)
{
	updateDayNightCycle(0.0005f);
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

void SkydomeWeatherComponent::AddRenderData(RenderDataGroup * collection)
{
	RenderPassPacket_SkyData data;
	RenderDataAttributes attributes;

	data._indexBuffer = _skydome->getIndexBuff();
	data._vertexBuffer = _skydome->getVertexBuff();

	data._numIndices = _skydome->numIndices;
	data._skyTexture = (IResource*)_tex;

	data._weatherApexColor = _weatherApexColor;
	data._weatherCenterColor = _weatherCenterColor;

	collection->addRenderData<RenderPassPacket_SkyData>(&data, RENDER_DATA_TYPE::SKY_RENDER_DATA, &attributes);
}

void SkydomeWeatherComponent::onEvent(EVENT_PTR evt)
{
}
