#include "../include/SkyRenderer.h"



SkyRenderer::SkyRenderer()
{
	_type = RENDERER_TYPE::SKY_RENDERER;
}


SkyRenderer::~SkyRenderer()
{
}

void SkyRenderer::DeferredInit()
{
	_wvp = Matrix4f::get_identity();
	_skyShader = _shaders.at("sky_shader");
}

void SkyRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_skyList = tree->queryNodesByType(RENDER_NODE_TYPE::SKYBOX_WEATHER_RENDER_NODE);
}

void SkyRenderer::processNodes(GraphicsCommandList * commandList)
{
	for each(RenderNode* skyNode in _skyList) {

		RenderParams* params = skyNode->getRenderParams();

		_skydomeApexColor = params->getPerNodeParam_skydomeApexColor();
		_skydomeCenterColor = params->getPerNodeParam_skydomeCenterColor();

		mesh* _sphereMesh = params->getPerNodeParam_Mesh();
		Texture* _cubeTex = params->getPerNodeParam_MeshTexture();
		CameraComponent* cam = params->getPerNodeParam_RenderCamera();

		Vector3f eyePos = cam->getPos();
		Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
		Matrix4f view = Matrix4f::transpose(cam->getViewMatrix());
		Matrix4f projection = Matrix4f::transpose(cam->getProjectionMatrix());

		_wvp = t * (view * projection);

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeWorldViewProj", &_wvp), _skyShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeApexColor", &_skydomeApexColor), _skyShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
			(std::make_pair("cbuff_skydomeCenterColor", &_skydomeCenterColor), _skyShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

		_ioInterface->assignHookResourceByName("index_buffer", _sphereMesh->getIndexBuff());
		_ioInterface->assignHookResourceByName("vertex_buffer", _sphereMesh->getVertexBuff());

		_ioInterface->assignHookResourceByName("skymap_texture", _cubeTex);

		commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_skyShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

		_pipelineState->setBlendState(BLEND_STATE::BLENDING_OFF);
		_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
		_pipelineState->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

		_pipelineState->shaderSetVertexInputLayout(_skyShader->getInputLayout());

		std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

		auto& constantBuffs = _skyShader->getConstantBuffers();

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

		_skyShader->execute(commandList);

		_pipelineState->reset();

		commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, _sphereMesh->numIndices),
			GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

		commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
	}
}
