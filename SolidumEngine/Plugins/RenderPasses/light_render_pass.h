#pragma once
#include "../../Solidum/sysInclude.h"

#include "../../Solidum/ResourceFramework/include/ResourceCreator.h"

#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"
#include "../../Solidum/GraphicsRendering/Shaders/include/ShaderUniformGroup.h"

#include "../../Solidum/GraphicsRendering/ShaderCommands/include/ShaderCommand.h"

#include "../../Solidum/EntityFramework/Components/include/LightComponent.h"

static void reg_render_pass__light(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback, ResourceCreator* resCreator) {
	
	RenderPassWrapper* wrapper = (RenderPassWrapper*)resCreator->createResourceImmediate<RenderPassWrapper>(&RenderPassWrapper::InitData("./res/RenderPassDescriptors/LightsRenderPass.txt", resCreator), "light_render_pass",
		[](IResource*) {});

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup& collection, RenderPassWrapper* wrapper)
	{
		std::list<RenderDataPacket*> renderData;
		collection.getRenderDataByType(RENDER_DATA_TYPE::RENDER_LIGHT_DATA, renderData);

		for each(RenderDataPacket* light in renderData) {

			RenderPassPacket_LightData* lightData = (RenderPassPacket_LightData*)light->getData();
			RenderData_GlobalData* globalData = collection.getGlobalData();

			ShaderUniformGroup globalDataUniforms;

			globalDataUniforms.setUniformCache(&wrapper->getSlabCache());

			globalDataUniforms.addUniform<Vector3f>(globalData->global_cam._eyePosition, "cbuff_eyePos");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._viewMatrix), "cbuff_viewMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._worldMatrix), "cbuff_worldMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._orthoProjection), "cbuff_orthoProjection");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._startView), "cbuff_camViewStart");

			ShaderUniformGroup lightDataUniforms;

			lightDataUniforms.setUniformCache(&wrapper->getSlabCache());

			lightDataUniforms.addUniform<Vector3f>(lightData->_lightDirection, "cbuff_lightDirection");
			lightDataUniforms.addUniform<Vector3f>(lightData->_lightPos, "cbuff_lightPos");
			lightDataUniforms.addUniform<Vector4f>(lightData->_lightColor, "cbuff_lightColor");
			lightDataUniforms.addUniform<float>(lightData->_intensity, "cbuff_lightIntensity");
			lightDataUniforms.addUniform<float>(lightData->_pointLightRange, "cbuff_pointLightRange");
			lightDataUniforms.addUniform<float>(lightData->_pointLightConstant, "cbuff_pointLightConstant");
			lightDataUniforms.addUniform<float>(lightData->_pointLightLinear, "cbuff_pointLightLinear");
			lightDataUniforms.addUniform<float>(lightData->_pointLightExponent, "cbuff_pointLightExponent");
			lightDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(lightData->_viewMatrix), "cbuff_lightViewMatrix");
			lightDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(lightData->_projectionMatrix), "cbuff_lightProjectionMatrix");

			wrapper->getIOInterface()->assignHookResourceByName("index_buffer", lightData->_indexBuff);
			wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", lightData->_vertexBuff);

			if (lightData->_lightType == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

				GPUPipeline pipelineState;

				IShader* directionalLightShader = wrapper->getShader("directional_light_shader");

				pipelineState.setBlendState(BLEND_STATE::ADDITIVE_BLENDING);
				pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);

				commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(globalDataUniforms, directionalLightShader));
				commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(lightDataUniforms, directionalLightShader));

				commandList->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(directionalLightShader));

				pipelineState.shaderSetVertexInputLayout(directionalLightShader->getInputLayout());

				std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

				auto& constantBuffs = directionalLightShader->getConstantBuffers();

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

				directionalLightShader->execute(commandList);

				commandList->createCommand<PipelineDrawIndexedCommand>(&PipelineDrawIndexedCommand::InitData(0, lightData->_indiceCount));

				commandList->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());
			}

			if (lightData->_lightType == LIGHT_TYPE::POINT_LIGHT) {

				GPUPipeline pipelineState;

				IShader* pointLightShader = wrapper->getShader("point_light_shader");

				pipelineState.setBlendState(BLEND_STATE::ADDITIVE_BLENDING);
				pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);


				commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(globalDataUniforms, pointLightShader));

				commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(lightDataUniforms, pointLightShader));


				commandList->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(pointLightShader));

				pipelineState.shaderSetVertexInputLayout(pointLightShader->getInputLayout());

				std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

				auto& constantBuffs = pointLightShader->getConstantBuffers();

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

				pointLightShader->execute(commandList);

				commandList->createCommand<PipelineDrawIndexedCommand>(&PipelineDrawIndexedCommand::InitData(0, lightData->_indiceCount));

				commandList->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());

			}
		}
	}
	);

	regCallback(std::shared_ptr<RenderPassWrapper>(wrapper));
}