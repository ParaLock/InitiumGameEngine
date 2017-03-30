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
	mesh* _mesh = nullptr;
	Texture* _texture = nullptr;
	Material* _material = nullptr;
public:
	MeshRenderNode(mesh* model, uint64_t id);
	~MeshRenderNode();

	void setTexture(Texture* tex) { _texture = tex; };
	void setMaterial(Material* mat) {

		_material = mat;
		_shader = mat->getPassList().at(0)->getShader();
	
	};

	Transform* getTransform() { return _renderParams.getPerNodeParam_Transform(); }
	mesh* getMesh() { return _mesh; };

	void render();
};

