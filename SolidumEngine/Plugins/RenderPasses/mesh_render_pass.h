#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"

#include "../../Solidum/EntityFramework/Components/include/MeshComponent.h"

static void reg_render_pass__mesh(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback) {
	std::shared_ptr<RenderPassWrapper> wrapper = std::make_shared<RenderPassWrapper>();;

	wrapper->load(std::make_shared<RenderPassWrapper::InitData>("./res/RenderPassDescriptors/MeshRenderPass.txt"));

	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup* collection, RenderPassWrapper* wrapper)
	{

		std::list<std::shared_ptr<RenderDataPacket>> renderData = collection->getRenderDataByType(RENDER_DATA_TYPE::RENDER_MESH_DATA);

		RenderData_GlobalData* globalData = collection->getGlobalData();

		std::shared_ptr<ShaderUniformGroup> globalDataUniforms = std::make_shared<ShaderUniformGroup>();

		globalDataUniforms->addUniform<Vector3f>(globalData->global_cam._eyePosition, "cbuff_eyePos");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._viewMatrix), "cbuff_viewMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._worldMatrix), "cbuff_worldMatrix");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._orthoProjection), "cbuff_orthoProjection");
		globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._startView), "cbuff_camViewStart");

		for each(std::shared_ptr<RenderDataPacket> mesh in renderData) {

			RenderPassPacket_MeshData* meshData = mesh->getData<RenderPassPacket_MeshData>();

			GPUPipeline pipelineState;

			std::shared_ptr<ShaderUniformGroup> meshDataUniforms = std::make_shared<ShaderUniformGroup>();
			std::shared_ptr<ShaderUniformGroup> materialDataUniforms = std::make_shared<ShaderUniformGroup>();

			meshDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(meshData->_globalTransform), "cbuff_OBJSpecificMatrix");

			IShader* _materialShader = nullptr;

			wrapper->getIOInterface()->assignHookResourceByName("index_buffer", meshData->_indiceBuffer);
			wrapper->getIOInterface()->assignHookResourceByName("vertex_buffer", meshData->_vertexBuffer);

			wrapper->getIOInterface()->assignHookResourceByName("color_texture", meshData->_modelTex);

			if (meshData->_materialData._textures.find(MATERIAL_TEX::NORMAL_MAT_TEXTURE) != meshData->_materialData._textures.end()) {
				_materialShader = wrapper->getShader("geo_shader_w_normal_mapping");
			}
			else {
				_materialShader = wrapper->getShader("geo_shader_no_normal_mapping");
			}

			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_albedo", nullptr);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_specular", nullptr);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_emessive", nullptr);
			wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_roughness", nullptr);

			materialDataUniforms->addUniform<float>(meshData->_materialData._specularIntensity, "cbuff_specularIntensity");
			materialDataUniforms->addUniform<Vector4f>(meshData->_materialData._specularColor, "cbuff_specularColor");
			materialDataUniforms->addUniform<float>(meshData->_materialData._specularPower, "cbuff_specularPower");

			const std::map<MATERIAL_TEX, Texture*>& materialTextures = meshData->_materialData._textures;

			for (auto itr = materialTextures.begin(); itr != materialTextures.end(); itr++) {
				switch (itr->first)
				{
				case MATERIAL_TEX::ALBEDO_MAT_TEXTURE:
					wrapper->getIOInterface()->assignHookResourceByName("mat_tex_albedo", itr->second);
					break;
				case MATERIAL_TEX::NORMAL_MAT_TEXTURE:
					wrapper->getIOInterface()->assignHookResourceByName("mat_tex_normal", itr->second);
					break;
				case MATERIAL_TEX::SPECULAR_MAT_TEXTURE:
					wrapper->getIOInterface()->assignHookResourceByName("mat_tex_specular", itr->second);
					break;
				case MATERIAL_TEX::EMESSIVE_PBR_TEXTURE:
					wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_emessive", itr->second);
					break;
				case MATERIAL_TEX::ROUGHNESS_PBR_TEXTURE:
					wrapper->getIOInterface()->assignHookResourceByName("mat_tex_pbr_roughness", itr->second);
					break;
				default:
					break;
				}
			}

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(globalDataUniforms, _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(meshDataUniforms, _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(materialDataUniforms, _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_materialShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

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

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, meshData->_numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);
		}

		commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
	}
	);

	regCallback(wrapper);
}