#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"
#include "../../Solidum/EntityFramework/Components/include/LightComponent.h"
#include "../../Solidum/EntityFramework/Components/include/MeshComponent.h"

static void reg_render_pass__shadowmap(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback) {
	std::shared_ptr<RenderPassWrapper> wrapper = std::make_shared<RenderPassWrapper>();;

	wrapper->load(std::make_shared<RenderPassWrapper::InitData>("./res/RenderPassDescriptors/ShadowMapRenderPass.txt"));

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup* collection, RenderPassWrapper* wrapper)
	{
		std::list<std::shared_ptr<RenderDataPacket>> lightRenderData = collection->getRenderDataByType(RENDER_DATA_TYPE::RENDER_LIGHT_DATA);
		std::list<std::shared_ptr<RenderDataPacket>> meshRenderData = collection->getRenderDataByType(RENDER_DATA_TYPE::RENDER_MESH_DATA);

		RenderData_GlobalData* globalData = collection->getGlobalData();

		std::shared_ptr<ShaderUniformGroup> globalDataUniforms = std::make_shared<ShaderUniformGroup>();

		globalDataUniforms->addUniform<Vector3f>(globalData->global_cam._eyePosition, "cbuff_eyePos");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._viewMatrix), "cbuff_viewMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._worldMatrix), "cbuff_worldMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._orthoProjection), "cbuff_orthoProjection");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._startView), "cbuff_camViewStart");

		IShader* shadowMapGenShader = wrapper->getShader("shadow_map_gen_shader");

		for each(std::shared_ptr<RenderDataPacket> light in lightRenderData) {

			RenderPassPacket_LightData* lightData = light->getData<RenderPassPacket_LightData>();

			for each(std::shared_ptr<RenderDataPacket> mesh in meshRenderData) {

				RenderPassPacket_MeshData* meshData = mesh->getData<RenderPassPacket_MeshData>();

				std::shared_ptr<ShaderUniformGroup> meshDataUniforms = std::make_shared<ShaderUniformGroup>();

				meshDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(meshData->_globalTransform), "cbuff_OBJSpecificMatrix");

				if (lightData->_lightType == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

					GPUPipeline pipelineState;

					std::shared_ptr<ShaderUniformGroup> lightDataUniforms = std::make_shared<ShaderUniformGroup>();

					lightDataUniforms->addUniform<Vector3f>(lightData->_lightDirection, "cbuff_lightDirection");
					lightDataUniforms->addUniform<Vector3f>(lightData->_lightPos, "cbuff_lightPos");
					lightDataUniforms->addUniform<Vector4f>(lightData->_lightColor, "cbuff_lightColor");
					lightDataUniforms->addUniform<float>(lightData->_intensity, "cbuff_lightIntensity");
					lightDataUniforms->addUniform<float>(lightData->_pointLightRange, "cbuff_pointLightRange");
					lightDataUniforms->addUniform<float>(lightData->_pointLightConstant, "cbuff_pointLightConstant");
					lightDataUniforms->addUniform<float>(lightData->_pointLightLinear, "cbuff_pointLightLinear");
					lightDataUniforms->addUniform<float>(lightData->_pointLightExponent, "cbuff_pointLightExponent");

					lightDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(lightData->_projectionMatrix), "cbuff_lightDepthProjection");
					lightDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(lightData->_viewMatrix), "cbuff_lightDepthView");

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(globalDataUniforms, shadowMapGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(lightDataUniforms, shadowMapGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
						(meshDataUniforms, shadowMapGenShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

					wrapper->getIOInterface()->assignHookResourceByName("index_buffer", meshData->_indiceBuffer);
					wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", meshData->_vertexBuffer);

					commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>
						(shadowMapGenShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

					pipelineState.setBlendState(BLEND_STATE::ADDITIVE_BLENDING);
					pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
					pipelineState.setRasterState(RASTER_STATE::NORMAL);

					pipelineState.shaderSetVertexInputLayout(shadowMapGenShader->getInputLayout());

					std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

					auto& constantBuffs = shadowMapGenShader->getConstantBuffers();

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
					shadowMapGenShader->execute(commandList);

					commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
						(0, meshData->_numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

					commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
				}
			}
		}
	}
	);

	regCallback(wrapper);
}