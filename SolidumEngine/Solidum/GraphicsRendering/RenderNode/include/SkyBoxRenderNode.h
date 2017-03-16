#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"
#include "../../../EngineUtils/include/Timer.h"

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

class SkyBoxRenderNode : public RenderNode
{
public:
	HRTimer _dayNightTimer;
private:
	float CURRENT_TIME = 0.0f;

	int _timeOfDayIndex = 0;

	TIME_OF_DAY_BLOCK _skyCycle[4] =
	{ { 2.7f, TIME_OF_DAY_CYCLE::MID_DAY, 1.0f, 1.5f, 1.5f, 1.5f, 1.5f, 1.5f }, 
	{ 0.6f, TIME_OF_DAY_CYCLE::SUN_SET, 0.5f, 0.06f, 0.06f, 0.06f, 0.06f, 0.06f }, 
	{ 4.0f, TIME_OF_DAY_CYCLE::NIGHT, 0.04f, 0.04f, 0.1f, 0.04f, 0.04f, 0.1f } };

	Texture* _cubeTex;
	mesh* _skydomeMesh;
	CameraComponent* _cam;

	Vector4f _skydomeCenterColor;
	Vector4f _skydomeApexColor;

	Vector4f _weatherCenterColor;
	Vector4f _weatherApexColor;

	Matrix4f _wvp;
public:
	SkyBoxRenderNode(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor);
	~SkyBoxRenderNode();

	void updateDayNightCycle(float delta);

	void render();
};

