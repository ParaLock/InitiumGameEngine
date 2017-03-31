#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"
#include "../../../EngineUtils/include/Timer.h"

#include "../../RenderNode/include/LightRenderNode.h"
#include "../../RenderNode/include/MeshRenderNode.h"

class ShadowGenRenderNode : public RenderNode
{
private:
public:
	ShadowGenRenderNode(IShader* shader, uint64_t id);
	~ShadowGenRenderNode();

	bool isRenderViable();

	void render();
};

