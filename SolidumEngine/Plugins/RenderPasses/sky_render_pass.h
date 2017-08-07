#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"

#include "../../Solidum/EntityFramework/Components/include/SkydomeWeatherComponent.h"

static void reg_render_pass__sky(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback, ResourceCreator* resCreator) {
	
	RenderPassWrapper* wrapper = (RenderPassWrapper*)resCreator->createResourceImmediate<RenderPassWrapper>(&RenderPassWrapper::InitData("./res/RenderPassDescriptors/SkyRenderPass.txt", resCreator), "sky_render_pass",
		[](IResource*) {});

	IShader* _skyShader = wrapper->getShader("sky_shader");

	_skyShader->updateGPU();

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup& collection, RenderPassWrapper* wrapper)
	{

		std::list<RenderDataPacket*> renderData;
		collection.getRenderDataByType(RENDER_DATA_TYPE::SKY_RENDER_DATA, renderData);

		for each(RenderDataPacket* sky in renderData) {

			RenderPassPacket_SkyData* skyData = (RenderPassPacket_SkyData*)sky->getData();
			RenderData_GlobalData* globalData = collection.getGlobalData();

			GPUPipeline pipelineState;

			IShader* _skyShader = wrapper->getShader("sky_shader");

			Vector3f eyePos = globalData->global_cam._eyePosition;
			Matrix4f t = Matrix4f::transpose(Matrix4f::get_translation(eyePos));
			Matrix4f view = Matrix4f::transpose(globalData->global_cam._viewMatrix);
			Matrix4f projection = Matrix4f::transpose(globalData->global_cam._projectionMatrix);

			Matrix4f wvp = (t * view * projection);

			ShaderUniformGroup skyDataUniforms;

			skyDataUniforms.setUniformCache(&wrapper->getSlabCache());

			skyDataUniforms.addUniform<Matrix4f>(wvp, "cbuff_skydomeWorldViewProj");
			skyDataUniforms.addUniform<Vector4f>(skyData->_weatherApexColor, "cbuff_skydomeApexColor");
			skyDataUniforms.addUniform<Vector4f>(skyData->_weatherCenterColor, "cbuff_skydomeCenterColor");

			commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(skyDataUniforms, _skyShader));

			wrapper->getIOInterface()->assignHookResourceByName(std::string("index_buffer"), skyData->_indexBuffer);
			wrapper->getIOInterface()->assignHookResourceByName(std::string("vertex_buffer"), skyData->_vertexBuffer);

			wrapper->getIOInterface()->assignHookResourceByName(std::string("skymap_texture"), skyData->_skyTexture);

			commandList->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(_skyShader));

			pipelineState.setBlendState(BLEND_STATE::BLENDING_OFF);
			pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			pipelineState.setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			pipelineState.shaderSetVertexInputLayout(_skyShader->getInputLayout());

			auto& constantBuffers = _skyShader->getConstantBuffers();

			for each(DynamicStruct* constBuff in constantBuffers) {

				pipelineState.attachResource(constBuff, constBuff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, constBuff->getTargetShaderType(), false);

			}

			wrapper->rebuildPSO(&pipelineState);

			pipelineState.applyState(commandList);

			_skyShader->execute(commandList);

			commandList->createCommand<PipelineDrawIndexedCommand>(&PipelineDrawIndexedCommand::InitData(0, skyData->_numIndices));

		}
		commandList->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());
	}
	);

	regCallback(std::shared_ptr<RenderPassWrapper>(wrapper));
}