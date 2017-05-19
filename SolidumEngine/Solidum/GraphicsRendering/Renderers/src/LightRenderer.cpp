#include "../include/LightRenderer.h"



LightRenderer::LightRenderer()
{
	_screenQuad = new mesh();
	_screenQuad->load(std::make_shared<mesh::InitData>(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_type = RENDERER_TYPE::LIGHT_RENDERER;
}


LightRenderer::~LightRenderer()
{
}

void LightRenderer::DeferredInit()
{
	_directionalLightShader = _shaders.at("directional_light_shader");
	_pointLightShader = _shaders.at("point_light_shader");
}

void LightRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_lights = tree->queryNodesByType(RENDER_NODE_TYPE::LIGHT_RENDER_NODE);
}

void LightRenderer::processNodes(GraphicsCommandList * commandList)
{
	for each(RenderNode* lightNode in _lights) {

		RenderParams* params = lightNode->getRenderParams();

		Light* light = params->getPerNodeParam_Light();

		static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getProjectionMatrix());
		static Matrix4f LviewMatrix = Matrix4f::transpose(light->getViewMatrix());

		static Matrix4f ShadowMatrix = light->getShadowMatrix();

		static Matrix4f CprojectionMatrix = params->getGlobalParam_GlobalRenderingCamera()->getProjectionMatrix();
		static Matrix4f CviewMatrix = params->getGlobalParam_GlobalRenderingCamera()->getViewMatrix();
		static Matrix4f CworldMatrix = params->getGlobalParam_GlobalRenderingCamera()->getWorldMatrix();
		static Matrix4f CmodelMatrix = params->getGlobalParam_GlobalRenderingCamera()->getModelMatrix();

		Vector3f lightPos = light->getPosition();

		static Matrix4f lightSpaceMatrix = LviewMatrix * LprojectionMatrix;

		_ioInterface->assignHookResourceByName("index_buffer", _screenQuad->getIndexBuff());
		_ioInterface->assignHookResourceByName("vertex_buffer", _screenQuad->getVertexBuff());

		if (light->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

			_pipelineState->setBlendState(BLEND_STATE::ADDITIVE_BLENDING);

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(params->getGlobalParam_GlobalRenderingCamera(), _directionalLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightViewMatrix", &LviewMatrix), _directionalLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightProjectionMatrix", &LprojectionMatrix), _directionalLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>
				(std::list<ILight*>{light}, _directionalLightShader, true), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_directionalLightShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_pipelineState->shaderSetVertexInputLayout(_directionalLightShader->getInputLayout());

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _directionalLightShader->getConstantBuffers();

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

			_directionalLightShader->execute(commandList);

			_pipelineState->reset();

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, _screenQuad->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}

		if (light->getType() == LIGHT_TYPE::POINT_LIGHT) {

			_pipelineState->setBlendState(BLEND_STATE::ADDITIVE_BLENDING);

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(params->getGlobalParam_GlobalRenderingCamera(), _pointLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightViewMatrix", &LviewMatrix), _pointLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightProjectionMatrix", &LprojectionMatrix), _pointLightShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>
				(std::list<ILight*>{light}, _pointLightShader, true), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_pointLightShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_pipelineState->shaderSetVertexInputLayout(_pointLightShader->getInputLayout());

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _pointLightShader->getConstantBuffers();

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

			_pointLightShader->execute(commandList);

			_pipelineState->reset();

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, _screenQuad->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);

		}
	}
}
