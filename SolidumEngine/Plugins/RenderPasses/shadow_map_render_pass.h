#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"
#include "../../Solidum/EntityFramework/Components/include/LightComponent.h"
#include "../../Solidum/EntityFramework/Components/include/MeshComponent.h"

static void reg_render_pass__shadowmap(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback, ResourceCreator* resCreator) {
	
	RenderPassWrapper* wrapper = (RenderPassWrapper*)resCreator->createResourceImmediate<RenderPassWrapper>(&RenderPassWrapper::InitData("./res/RenderPassDescriptors/ShadowMapRenderPass.txt", resCreator), "shadow_map_render_pass",
		[=](IResource* res) {/*return IResource::addResourceToGroup(res, std::string("RenderPassWrapperGroup"), resCreator->getParentEngine());*/ });

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup& collection, RenderPassWrapper* wrapper)
	{
		std::list<RenderDataPacket*> lightRenderData;
		
		collection.getRenderDataByType(RENDER_DATA_TYPE::RENDER_LIGHT_DATA, lightRenderData);
		
		std::list<RenderDataPacket*> meshRenderData;
		
		collection.getRenderDataByType(RENDER_DATA_TYPE::RENDER_MESH_DATA, meshRenderData);

		RenderData_GlobalData* globalData = collection.getGlobalData();

		IShader* shadowMapGenShader = wrapper->getShader("shadow_map_gen_shader");

		for each(RenderDataPacket* light in lightRenderData) {

			ShaderUniformGroup globalDataUniforms;

			globalDataUniforms.setUniformCache(&wrapper->getSlabCache());

			globalDataUniforms.addUniform<Vector3f>(globalData->global_cam._eyePosition, "cbuff_eyePos");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._viewMatrix), "cbuff_viewMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._worldMatrix), "cbuff_worldMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._orthoProjection), "cbuff_orthoProjection");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._startView), "cbuff_camViewStart");


			RenderPassPacket_LightData* lightData = (RenderPassPacket_LightData*)light->getData();

			for each(RenderDataPacket* mesh in meshRenderData) {

				RenderPassPacket_MeshData* meshData = (RenderPassPacket_MeshData*)mesh->getData();

				ShaderUniformGroup meshDataUniforms;

				meshDataUniforms.setUniformCache(&wrapper->getSlabCache());

				meshDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(meshData->_globalTransform), "cbuff_OBJSpecificMatrix");

				if (lightData->_lightType == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

					GPUPipeline pipelineState;

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

					lightDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(lightData->_projectionMatrix), "cbuff_lightDepthProjection");
					lightDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(lightData->_viewMatrix), "cbuff_lightDepthView");

					commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(globalDataUniforms, shadowMapGenShader));

					commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(lightDataUniforms, shadowMapGenShader));

					commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(meshDataUniforms, shadowMapGenShader));

					wrapper->getIOInterface()->assignHookResourceByName("index_buffer", meshData->_indiceBuffer);
					wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", meshData->_vertexBuffer);

					commandList->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(shadowMapGenShader));

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

						pipelineState.attachResource((IResource*)buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
					}


					wrapper->rebuildPSO(&pipelineState);

					pipelineState.applyState(commandList);
					shadowMapGenShader->execute(commandList);

					commandList->createCommand<PipelineDrawIndexedCommand>(&PipelineDrawIndexedCommand::InitData(0, meshData->_numIndices));

					commandList->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());
				}
			}
		}
	}
	);

	regCallback(std::shared_ptr<RenderPassWrapper>(wrapper));
}