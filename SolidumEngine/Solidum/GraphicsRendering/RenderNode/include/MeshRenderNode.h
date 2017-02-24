#pragma once
#include "RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"

class MaterialPass;

class MeshRenderNode : public RenderNode
{
private:
	mesh* _mesh;
	Texture* _texture;
	MaterialPass* _pass;
public:
	MeshRenderNode(mesh* mesh, Texture* texture, MaterialPass* pass);
	~MeshRenderNode();

	void render();
};

