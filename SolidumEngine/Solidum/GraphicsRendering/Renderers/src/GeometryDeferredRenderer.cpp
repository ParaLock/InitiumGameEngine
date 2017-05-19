#include "../include/GeometryDeferredRenderer.h"


GeometryDeferredRenderer::GeometryDeferredRenderer()
{
	_type = RENDERER_TYPE::GEOMETRY_DEFERRED_RENDERER;
}


GeometryDeferredRenderer::~GeometryDeferredRenderer()
{
}

void GeometryDeferredRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_staticMeshes = tree->queryNodesByType(RENDER_NODE_TYPE::MESH_RENDER_NODE);
}

void GeometryDeferredRenderer::processNodes(GraphicsCommandList * commandList)
{
	for each(RenderNode* meshNode in _staticMeshes) {

		RenderParams* params = meshNode->getRenderParams();

		Material* _material = params->getPerNodeParam_MeshMaterial();
		Texture* _texture = params->getPerNodeParam_MeshTexture();
		mesh* _mesh = params->getPerNodeParam_Mesh();
		Transform* transform = params->getPerNodeParam_Transform();

		IShader* _materialShader = nullptr;

		_ioInterface->assignHookResourceByName("index_buffer", _mesh->getIndexBuff());
		_ioInterface->assignHookResourceByName("vertex_buffer", _mesh->getVertexBuff());

		_ioInterface->assignHookResourceByName("color_texture", _texture);

		if (_material->getPassList().at(0)->getTextures().find(MATERIAL_TEX::NORMAL_MAT_TEXTURE) != _material->getPassList().at(0)->getTextures().end()) {
			_materialShader = (Shader*)_shaders.at("geo_shader_w_normal_mapping");
		}
		else {
			_materialShader = (Shader*)_shaders.at("geo_shader_no_normal_mapping");
		}

		_materialShader->updateMaterialPassUniforms(_material->getPassList().at(0), _ioInterface);

		commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
			(params->getGlobalParam_GlobalRenderingCamera(), _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

		commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>
			(transform, _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

		commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_materialShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

		if (!params->getPerNodeParam_DepthTestEnableState()) {

			_pipelineState->setBlendState(BLEND_STATE::ALPHA_BLENDING);
			_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
			_pipelineState->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

		}

		_pipelineState->setBlendState(BLEND_STATE::BLENDING_OFF);
		_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
		_pipelineState->setRasterState(RASTER_STATE::NORMAL);

		_pipelineState->shaderSetVertexInputLayout(_materialShader->getInputLayout());

		std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

		auto& constantBuffs = _materialShader->getConstantBuffers();

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

		_materialShader->execute(commandList);

		_pipelineState->reset();

		commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
			(0, _mesh->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

	}

	commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
}
