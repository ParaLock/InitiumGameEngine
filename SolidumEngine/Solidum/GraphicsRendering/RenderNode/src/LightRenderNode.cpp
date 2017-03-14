#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode(Light* light) :
	_light(light)
{
	_orthoMesh = new mesh();
	_orthoMesh->load(&meshBuilder(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_shader = ResourceManagerPool::getInstance()->getResourceManagerSpecific<LightManager>
		("LightManager")->getLightShader(_light->getType());

	_type = RENDER_NODE_TYPE::LIGHT_RENDER_NODE;
}


LightRenderNode::~LightRenderNode()
{
	delete _orthoMesh;
}

void LightRenderNode::render()
{
	if (_isVisible) {

		if (_shader->getRenderMode() != SHADER_RENDER_TYPE::FORWARD_RENDERING) {

			//Hooks must be set in immediate context
			_shader->setMesh(_orthoMesh);

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateCameraUniformsCommand(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderSyncUniforms(_shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateLightUniformsCommand(std::vector<ILight*>{_light}, _shader));


			_shader->execute(_orthoMesh->numIndices);
		}

		_isVisible = false;
	}
}
