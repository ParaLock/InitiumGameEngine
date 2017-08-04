#pragma once
#include "../../Solidum/sysInclude.h"

#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"

#include "../../Solidum/EntityFramework/Components/include/MeshComponent.h"

#include "../../Solidum/GraphicsRendering/ShaderCommands/include/ShaderCommand.h"

static void reg_render_pass__mesh(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback, ResourceCreator* resCreator) {
	
	RenderPassWrapper* wrapper = (RenderPassWrapper*)resCreator->createResourceImmediate<RenderPassWrapper>(&RenderPassWrapper::InitData("./res/RenderPassDescriptors/MeshRenderPass.txt", resCreator), "mesh_render_pass",
		[](IResource*) {});

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup& collection, RenderPassWrapper* wrapper)
	{

		std::list<RenderDataPacket*> renderData;
		collection.getRenderDataByType(RENDER_DATA_TYPE::RENDER_MESH_DATA, renderData);

		RenderData_GlobalData* globalData = collection.getGlobalData();

		for each(RenderDataPacket* mesh in renderData) {

			ShaderUniformGroup globalDataUniforms;

			globalDataUniforms.setUniformCache(&wrapper->getSlabCache());

			globalDataUniforms.addUniform<Vector3f>(globalData->global_cam._eyePosition, "cbuff_eyePos");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._viewMatrix), "cbuff_viewMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._worldMatrix), "cbuff_worldMatrix");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._orthoProjection), "cbuff_orthoProjection");
			globalDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._startView), "cbuff_camViewStart");


			RenderPassPacket_MeshData* meshData = (RenderPassPacket_MeshData*)mesh->getData();

			GPUPipeline pipelineState;

			ShaderUniformGroup meshDataUniforms;

			meshDataUniforms.setUniformCache(&wrapper->getSlabCache());

			ShaderUniformGroup materialDataUniforms;

			materialDataUniforms.setUniformCache(&wrapper->getSlabCache());

			meshDataUniforms.addUniform<Matrix4f>(Matrix4f::transpose(meshData->_globalTransform), "cbuff_OBJSpecificMatrix");

			IShader* _materialShader = nullptr;

			wrapper->getIOInterface()->assignHookResourceByName("index_buffer", meshData->_indiceBuffer);
			wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", meshData->_vertexBuffer);

			wrapper->getIOInterface()->assignHookResourceByName("color_texture", meshData->_modelTex);

			_materialShader = wrapper->getShader("geo_shader_no_normal_mapping");

			if (meshData->_materialData._normalTex != nullptr) {

				_materialShader = wrapper->getShader("geo_shader_w_normal_mapping");

				wrapper->getIOInterface()->assignHookResourceByName("mat_tex_normal", meshData->_materialData._normalTex);
			}

			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_albedo", meshData->_materialData._albedoTex);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_specular", meshData->_materialData._specularTex);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_emessive", meshData->_materialData._emissiveTex);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_roughness", meshData->_materialData._roughnessTex);

			materialDataUniforms.addUniform<float>(meshData->_materialData._specularIntensity, "cbuff_specularIntensity");
			materialDataUniforms.addUniform<Vector4f>(meshData->_materialData._specularColor, "cbuff_specularColor");
			materialDataUniforms.addUniform<float>(meshData->_materialData._specularPower, "cbuff_specularPower");

			commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(globalDataUniforms, _materialShader));
			commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(meshDataUniforms, _materialShader));
			commandList->createCommand<ShaderUpdateUniformCommand>(&ShaderUpdateUniformCommand::InitData(materialDataUniforms, _materialShader));

			commandList->createCommand<ShaderSyncUniforms>(&ShaderSyncUniforms::InitData(_materialShader));

			pipelineState.setBlendState(BLEND_STATE::BLENDING_OFF);
			pipelineState.setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
			pipelineState.setRasterState(RASTER_STATE::NORMAL);

			pipelineState.shaderSetVertexInputLayout(_materialShader->getInputLayout());

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _materialShader->getConstantBuffers();

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

			_materialShader->execute(commandList);

			commandList->createCommand<PipelineDrawIndexedCommand>(&PipelineDrawIndexedCommand::InitData(0, meshData->_numIndices));
		}

		commandList->createCommand<PipelineStateResetCommand>(&PipelineStateResetCommand::InitData());
	}
	);

	regCallback(std::shared_ptr<RenderPassWrapper>(wrapper));
}