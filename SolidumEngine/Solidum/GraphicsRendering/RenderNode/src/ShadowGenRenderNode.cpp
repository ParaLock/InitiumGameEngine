#include "../include/ShadowGenRenderNode.h"



ShadowGenRenderNode::ShadowGenRenderNode()
{
}


ShadowGenRenderNode::~ShadowGenRenderNode()
{
}

void ShadowGenRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_shader = realBuilder->_shader;
	_id = realBuilder->_id;

	isLoaded = true;
}

void ShadowGenRenderNode::unload()
{
	isLoaded = false;
}

bool ShadowGenRenderNode::isRenderViable()
{
	return true;
}

void ShadowGenRenderNode::render()
{
	int start_s = clock();

	GraphicsCommandList* commandList = new GraphicsCommandList();

	std::vector<RenderNode*> lights = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllShadowCastingLights();

	std::vector<RenderNode*> meshes = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllMeshes();


	for each(RenderNode* node in lights) {
		LightRenderNode* light = (LightRenderNode*)node;

		if (light->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

			for each(RenderNode* meshNode in meshes) {

				MeshRenderNode* mesh = (MeshRenderNode*)meshNode;

				if (mesh->isRenderViable()) {

					GraphicsCore* gCore = GraphicsCore::getInstance();
					GraphicsCommandPool* commandPool = gCore->getGraphicsCommandPool();

					GraphicsCommand* camUpdate					= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);
					GraphicsCommand* updateUniform_LightProj    = commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
					GraphicsCommand* updateUniform_LightView    = commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
					GraphicsCommand* updateUniform_LightPos     = commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					GraphicsCommand* updateTransform			= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

					GraphicsCommand* syncUniforms				= commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

					GraphicsCommand* drawIndexedModel = commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);
					GraphicsCommand* resetPipeline = commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);

					syncUniforms->load(std::make_shared<ShaderSyncUniforms::InitData>(_shader));

					static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getLight()->getProjectionMatrix());
					static Matrix4f LviewMatrix = Matrix4f::transpose(light->getLight()->getViewMatrix());

					static Vector3f lightPos = light->getLight()->getPosition();

					updateUniform_LightProj->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightProjectionMatrix", &LprojectionMatrix), _shader));

					updateUniform_LightView->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightViewMatrix", &LviewMatrix), _shader));

					updateUniform_LightPos->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightPos", &lightPos), _shader));

					camUpdate->load(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
						(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

					updateTransform->load(std::make_shared<ShaderUpdateTransformCommand::InitData>
						(mesh->getTransform(), _shader));

					drawIndexedModel->load(std::make_shared<PipelineDrawIndexedCommand::InitData>
						(0, mesh->getMesh()->numIndices));

					commandList->queueCommand(camUpdate);

					commandList->queueCommand(updateUniform_LightProj);

					commandList->queueCommand(updateUniform_LightView);

					commandList->queueCommand(updateUniform_LightPos);

					_shader->setMesh(mesh->getMesh());

					commandList->queueCommand(updateTransform);

					commandList->queueCommand(syncUniforms);

					_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
					_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
					_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);

					_shader->execute(commandList);

					commandList->queueCommand(drawIndexedModel);
					commandList->queueCommand(resetPipeline);
				}
			}
		}
	}

	_renderParams.setPerNodeParam_isVisible(false);

	commandList->queueCommand(new PipelineClearDepthStencil());

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);


	int stop_s = clock();
	std::cout << "RENDER NODE EXECUTE TIME: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << std::endl;
}
