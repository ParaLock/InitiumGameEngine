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

	Vector4f _skydomeCenterColor;
	Vector4f _skydomeApexColor;

	Matrix4f _wvp;
public:
	SkyBoxRenderNode(IShader * shader, Vector4f apexColor, Vector4f centerColor, uint64_t id);
	~SkyBoxRenderNode();

	bool isRenderViable();

	void render();
};

