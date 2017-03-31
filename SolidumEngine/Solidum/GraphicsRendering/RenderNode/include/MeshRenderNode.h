#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"

#include "../include/LightRenderNode.h"

#include "../../Material/include/Material.h"

class MeshRenderNode : public RenderNode
{
private:
public:
	MeshRenderNode(uint64_t id);
	~MeshRenderNode();

	Transform* getTransform() { return _renderParams.getPerNodeParam_Transform(); }

	mesh* getMesh() { return _renderParams.getPerNodeParam_Mesh(); }

	bool isRenderViable();

	void render();
};

