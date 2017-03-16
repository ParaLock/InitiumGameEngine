#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"
#include "../../../EngineUtils/include/Timer.h"


class SkyBoxRenderNode : public RenderNode
{
public:
private:

	Texture* _cubeTex;
	mesh* _skydomeMesh;
	CameraComponent* _cam;

	Vector4f _skydomeCenterColor;
	Vector4f _skydomeApexColor;

	Matrix4f _wvp;
public:
	SkyBoxRenderNode(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam, Vector4f apexColor, Vector4f centerColor);
	~SkyBoxRenderNode();

	void render();
};

