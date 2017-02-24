#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode(Light* light) :
	_light(light)
{
	_orthoMesh = new mesh();
	_orthoMesh->load(&meshBuilder(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_shader = ResourceManagerPool::getInstance()->getResourceManagerSpecific<LightManager>
		("LightManager")->getLightShader(_light->getType());
}


LightRenderNode::~LightRenderNode()
{
	delete _orthoMesh;
}

void LightRenderNode::render()
{
	if (_isVisible) {

		_shader->setMesh(_orthoMesh);
		_shader->updateLightUniforms(_light);
		_shader->updateCameraUniforms(_renderParams.getGlobalParam_GlobalRenderingCamera());

		_shader->updateGPU();
		_shader->execute(_orthoMesh->numIndices);

		_isVisible = false;
	}
}
