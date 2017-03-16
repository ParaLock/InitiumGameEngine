#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode(IShader * shader, Texture * tex, mesh * skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor)
{
	_shader = shader;
	_cubeTex = tex;
	_skydomeMesh = skydome;
	_cam = cam;

	_skydomeApexColor = apexColor;
	_skydomeCenterColor = centerColor;

	_weatherApexColor = apexColor;
	_weatherCenterColor = centerColor;

	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

void SkyBoxRenderNode::updateDayNightCycle(float delta)
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

void SkyBoxRenderNode::render()
{
	Vector3f eyePos = _cam->getPos();
	Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
	Matrix4f view = Matrix4f::transpose(_cam->getViewMatrix());
	Matrix4f projection = Matrix4f::transpose(_cam->getProjectionMatrix());

    _wvp = t * (view * projection);

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_wvp, "cbuff_skydomeWorldViewProj", _shader));

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_weatherApexColor, "cbuff_skydomeApexColor", _shader));

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderUpdateUniformCommand(&_weatherCenterColor, "cbuff_skydomeCenterColor", _shader));

	updateDayNightCycle(0.0005f);

	//Resource Hooks must be set in immediate context
	_shader->setMesh(_skydomeMesh);
	_shader->setMiscResourceHook(_cubeTex, "sky_tex");

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new ShaderSyncUniforms(_shader));

	_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
	_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
	_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

	_shader->execute(_skydomeMesh->numIndices);
}
