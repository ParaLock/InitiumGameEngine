#include "../include/MeshRenderNode.h"



MeshRenderNode::MeshRenderNode(mesh* mesh, Texture* texture, MaterialPass* pass) :
	_mesh(mesh),
	_texture(texture),
	_pass(pass)
{
	_shader = _pass->getShader();


	int debugRef = -1;
}


MeshRenderNode::~MeshRenderNode()
{
}

void MeshRenderNode::render()
{
	if (_isVisible) {

		_shader->updateCameraUniforms(_renderParams.getGlobalParam_GlobalRenderingCamera());

		_shader->setMesh(_mesh);

		_shader->setModelTexture(_texture);

		_shader->updateMaterialPassUniforms(_pass);

		_shader->updateModelUniforms(_renderParams.getPerNodeParam_Transform());

		_shader->updateGPU();
		_shader->execute(_mesh->numIndices);
	
		_isVisible = false;
	}
}
