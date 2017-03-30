#include "../include/MeshRenderNode.h"



MeshRenderNode::MeshRenderNode(mesh* model, uint64_t id) :
	_mesh(model)
{
	_id = id;

	_type = RENDER_NODE_TYPE::MESH_RENDER_NODE;
}


MeshRenderNode::~MeshRenderNode()
{
}

void MeshRenderNode::render()
{
	_isVisible = _renderParams.getPerNodeParam_isVisible();

	if (_isVisible) {

		if (_shader->getRenderMode() == SHADER_RENDER_TYPE::FORWARD_RENDERING) {

			std::vector<RenderNode*> lightNodes = GraphicsCore::getInstance()->getRenderNodeTree()->queryAllLights();

			std::vector<ILight*> pointLights;
			std::vector<ILight*> directionalLights;

			for each (RenderNode* node in lightNodes) {
				LightRenderNode* lightNode = (LightRenderNode*)node;

				if (lightNode->getLight()->getType() == LIGHT_TYPE::POINT_LIGHT)
					pointLights.push_back(lightNode->getLight());
				if (lightNode->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT)
					directionalLights.push_back(lightNode->getLight());
			}

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateLightUniformsCommand(pointLights, _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateLightUniformsCommand(directionalLights, _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateCameraUniformsCommand(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

			//Hooks must be set in immediate context
			_shader->setMesh(_mesh);
			_shader->setModelTexture(_texture);
			_shader->updateMaterialPassUniforms(_material->getPassList().at(0));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateTransformCommand(_renderParams.getPerNodeParam_Transform(), _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderSyncUniforms(_shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new PipelineSetBlendStateCommand(BLEND_STATE::BLENDING_OFF));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new PipelineSetDepthTestStateCommand(DEPTH_TEST_STATE::FULL_ENABLE));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new PipelineSetRasterStateCommand(RASTER_STATE::NORMAL));

			_shader->execute(_mesh->numIndices);
		}
		else {

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateCameraUniformsCommand(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

			//Hooks must be set in immediate context
			_shader->setMesh(_mesh);
			_shader->setModelTexture(_texture);
			_shader->updateMaterialPassUniforms(_material->getPassList().at(0));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateTransformCommand(_renderParams.getPerNodeParam_Transform(), _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderSyncUniforms(_shader));

			if (!_renderParams.getPerNodeParam_DepthTestEnableState()) {


				_shader->getPipeline()->setBlendState(BLEND_STATE::PASS_BLENDING);
				_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
				_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			}

			_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
			_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
			_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);

			_shader->execute(_mesh->numIndices);
		}
	}
	_isVisible = false;
}
