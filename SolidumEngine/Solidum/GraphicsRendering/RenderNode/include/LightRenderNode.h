#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"

#include "../../Shaders/include/Shader.h"

#include "../../Lights/include/Light.h"

#include "../../Lights/include/LightManager.h"

class LightRenderNode : public RenderNode
{
private:
	mesh* _orthoMesh;
	Light* _light;
public:
	LightRenderNode(Light* light);
	~LightRenderNode();

	void render();
};

