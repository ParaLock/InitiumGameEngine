#include "../include/ShadowMapRenderer.h"



ShadowMapRenderer::ShadowMapRenderer()
{
	_type = RENDERER_TYPE::SHADOW_RENDERER;
}


ShadowMapRenderer::~ShadowMapRenderer()
{
}

void ShadowMapRenderer::DeferredInit()
{
	_shadowGenShader = _shaders.at("shadow_map_gen_shader");
}

void ShadowMapRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_lights = tree->queryNodesByType(RENDER_NODE_TYPE::LIGHT_RENDER_NODE);
	_meshes = tree->queryNodesByType(RENDER_NODE_TYPE::MESH_RENDER_NODE);
}

void ShadowMapRenderer::processNodes(GraphicsCommandList * commandList)
{
	for each(RenderNode* node in _lights) {

		RenderParams* lightParams = node->getRenderParams();

		LightRenderNode* light = (LightRenderNode*)node;

		if (light->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

			light->getLight()->shadowUpdate(lightParams->getGlobalParam_WorldBoundingSphere());

			for each(RenderNode* meshNode in _meshes) {

				MeshRenderNode* mesh = (MeshRenderNode*)meshNode;

				if (mesh->isRenderViable()) {

					CameraComponent* cam = lightParams->getGlobalParam_GlobalRenderingCamera();
					Transform* meshTransform = mesh->getRenderParams()->getPerNodeParam_Transform();

					RenderParams* meshParams = mesh->getRenderParams();

					static Vector3f lightPos = light->getLight()->getPosition();

					static Matrix4f LShadowMatrix = light->getLight()->getShadowMatrix();

					static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getLight()->getProjectionMatrix());

					static Matrix4f LviewMatrix = Matrix4f::transpose(light->getLight()->getViewMatrix());

					commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
						(lightParams->getGlobalParam_GlobalRenderingCamera(), _shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightDepthProjection", &LprojectionMatrix), _shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightDepthView", &LviewMatrix), _shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(std::make_pair("cbuff_lightPos", &lightPos), _shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					_ioInterface->assignHookResourceByName("index_buffer", meshParams->getPerNodeParam_Mesh()->getIndexBuff());
					_ioInterface->assignHookResourceByName("vertex_buffer", meshParams->getPerNodeParam_Mesh()->getVertexBuff());

					commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>
						(mesh->getTransform(), _shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

					commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>
						(_shadowGenShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

					_pipelineState->setBlendState(BLEND_STATE::BLENDING_OFF);
					_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
					_pipelineState->setRasterState(RASTER_STATE::NORMAL);


					_pipelineState->shaderSetVertexInputLayout(_shadowGenShader->getInputLayout());

					std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

					auto& constantBuffs = _shadowGenShader->getConstantBuffers();

					for (auto itr = constantBuffs.begin(); itr != constantBuffs.end(); itr++) {

						singleStructs.insert(itr->second);
					}

					for (auto itr = singleStructs.begin(); itr != singleStructs.end(); itr++) {

						std::pair<SHADER_TYPE, DynamicStruct*> data = *itr;

						DynamicStruct* buff = data.second;

						_pipelineState->attachResource(buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
					}


					rebuildPSO();

					_pipelineState->applyState(commandList);
					_shadowGenShader->execute(commandList);

					_pipelineState->reset();

					commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
						(0, mesh->getMesh()->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

					commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
				}
			}
		}
	}
}
