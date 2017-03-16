#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"


class SkyBoxRenderNode : public RenderNode
{
private:
	Texture* _cubeTex;
	mesh* _skydomeMesh;
	CameraComponent* _cam;

	Vector4f _skydomeCenterColor;
	Vector4f _skydomeApexColor;

	Matrix4f _wvp;
public:
	SkyBoxRenderNode(IShader* shader, Texture* tex, mesh* skydome, CameraComponent* cam);
	~SkyBoxRenderNode();

	void render();
};

