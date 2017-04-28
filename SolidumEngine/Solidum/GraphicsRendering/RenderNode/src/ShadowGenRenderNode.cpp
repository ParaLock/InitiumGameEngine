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
	GraphicsCommandList* commandList = new GraphicsCommandList();

	std::vector<RenderNode*> lights = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllShadowCastingLights();

	std::vector<RenderNode*> meshes = GraphicsCore::getInstance()->
		getRenderNodeTree()->queryAllMeshes();


	for each(RenderNode* node in lights) {
		LightRenderNode* light = (LightRenderNode*)node;

		if (light->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

			light->getLight()->shadowUpdate(_renderParams.getGlobalParam_WorldBoundingSphere());

			for each(RenderNode* meshNode in meshes) {

				MeshRenderNode* mesh = (MeshRenderNode*)meshNode;

				if (mesh->isRenderViable()) {

					CameraComponent* cam = _renderParams.getGlobalParam_GlobalRenderingCamera();
					Transform* meshTransform = mesh->getRenderParams()->getPerNodeParam_Transform();


					static Vector3f lightPos = light->getLight()->getPosition();

					static Matrix4f LShadowMatrix = light->getLight()->getShadowMatrix();

					static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getLight()->getProjectionMatrix());

					static Matrix4f LviewMatrix = Matrix4f::transpose(light->getLight()->getViewMatrix());

					commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
						(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightDepthProjection", &LprojectionMatrix), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightDepthView", &LviewMatrix), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightPos", &lightPos), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					_shader->setMesh(mesh->getMesh());

					commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>
						(mesh->getTransform(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

					commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>
						(_shader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

					_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
					_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
					_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);

					_shader->execute(commandList);

					commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
						(0, mesh->getMesh()->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

					commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
				}
			}
		}
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);
}
