#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"

#include "../../Solidum/EntityFramework/Components/include/SkydomeWeatherComponent.h"

static void reg_render_pass__sky(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback) {
	std::shared_ptr<RenderPassWrapper> wrapper = std::make_shared<RenderPassWrapper>();

	wrapper->load(std::make_shared<RenderPassWrapper::InitData>("./res/RenderPassDescriptors/SkyRenderPass.txt"));

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup* collection, RenderPassWrapper* wrapper)
	{

		std::list<std::shared_ptr<RenderDataPacket>> renderData = collection->getRenderDataByType(RENDER_DATA_TYPE::SKY_RENDER_DATA);

		for each(std::shared_ptr<RenderDataPacket> sky in renderData) {

			RenderPassPacket_SkyData* skyData = sky->getData<RenderPassPacket_SkyData>();
			RenderData_GlobalData* globalData = collection->getGlobalData();

			GPUPipeline pipelineState;

			IShader* _skyShader = wrapper->getShader("sky_shader");

			Vector3f eyePos = globalData->global_cam._eyePosition;
			Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
			Matrix4f view = Matrix4f::transpose(globalData->global_cam._viewMatrix);
			Matrix4f projection = Matrix4f::transpose(globalData->global_cam._projectionMatrix);

			Matrix4f wvp = (t * view * projection);

			std::shared_ptr<ShaderUniformGroup> skyDataUniforms = std::make_shared<ShaderUniformGroup>();

			skyDataUniforms->addUniform<Matrix4f>(wvp, "cbuff_skydomeWorldViewProj");
			skyDataUniforms->addUniform<Vector4f>(skyData->_weatherApexColor, "cbuff_skydomeApexColor");
			skyDataUniforms->addUniform<Vector4f>(skyData->_weatherCenterColor, "cbuff_skydomeCenterColor");

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(skyDataUniforms, _skyShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			wrapper->getIOInterface()->assignHookResourceByName("index_buffer", skyData->_indexBuffer);
			wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", skyData->_vertexBuffer);

			wrapper->getIOInterface()->assignHookResourceByName("skymap_texture", skyData->_skyTexture);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_skyShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			pipelineState.setBlendState(BLEND_STATE::BLENDING_OFF);
			pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			pipelineState.setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			pipelineState.shaderSetVertexInputLayout(_skyShader->getInputLayout());

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _skyShader->getConstantBuffers();

			for (auto itr = constantBuffs.begin(); itr != constantBuffs.end(); itr++) {

				singleStructs.insert(itr->second);
			}

			for (auto itr = singleStructs.begin(); itr != singleStructs.end(); itr++) {

				std::pair<SHADER_TYPE, DynamicStruct*> data = *itr;

				DynamicStruct* buff = data.second;

				pipelineState.attachResource(buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
			}


			wrapper->rebuildPSO(&pipelineState);

			pipelineState.applyState(commandList);

			_skyShader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, skyData->_numIndices),
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

		}
		commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
	}
	);

	regCallback(wrapper);
}