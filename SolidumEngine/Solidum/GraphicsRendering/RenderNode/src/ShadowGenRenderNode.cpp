#include "../include/ShadowGenRenderNode.h"



ShadowGenRenderNode::ShadowGenRenderNode(IShader* shader, uint64_t id)
{

	_shader = shader;
}


ShadowGenRenderNode::~ShadowGenRenderNode()
{
}

bool ShadowGenRenderNode::isRenderViable()
{
	return true;
}

void ShadowGenRenderNode::render()
{
	std::vector<RenderNode*> lights = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllShadowCastingLights();

	std::vector<RenderNode*> meshes = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllMeshes();


	for each(RenderNode* node in lights) {
		LightRenderNode* light = (LightRenderNode*)node;

		if (light->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {


			for each(RenderNode* meshNode in meshes) {

				MeshRenderNode* mesh = (MeshRenderNode*)meshNode;

				static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getLight()->getProjectionMatrix());
				static Matrix4f LviewMatrix = Matrix4f::transpose(light->getLight()->getViewMatrix());


				static Vector3f lightPos = light->getLight()->getPosition();

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderUpdateCameraUniformsCommand(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderUpdateUniformCommand(&LprojectionMatrix, "cbuff_lightProjectionMatrix", _shader));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderUpdateUniformCommand(&LviewMatrix, "cbuff_lightViewMatrix", _shader));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderUpdateUniformCommand(&lightPos, "cbuff_lightPos", _shader));

				_shader->setMesh(mesh->getMesh());

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderUpdateTransformCommand(mesh->getTransform(), _shader));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new ShaderSyncUniforms(_shader));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSetBlendStateCommand(BLEND_STATE::BLENDING_OFF));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSetDepthTestStateCommand(DEPTH_TEST_STATE::FULL_ENABLE));

				GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
					new PipelineSetRasterStateCommand(RASTER_STATE::NORMAL));

				_shader->execute(mesh->getMesh()->numIndices);
			}
		}
	}

	GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
		new PipelineClearDepthStencil());
}
