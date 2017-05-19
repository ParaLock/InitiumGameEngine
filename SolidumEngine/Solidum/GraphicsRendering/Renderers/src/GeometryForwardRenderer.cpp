#include "../include/GeometryForwardRenderer.h"



GeometryForwardRenderer::GeometryForwardRenderer()
{
	_type = RENDERER_TYPE::GEOMETRY_FORWARD_RENDERER;
}


GeometryForwardRenderer::~GeometryForwardRenderer()
{
}

void GeometryForwardRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_staticMeshes = tree->queryNodesByType(RENDER_NODE_TYPE::MESH_RENDER_NODE);
}

void GeometryForwardRenderer::processNodes(GraphicsCommandList * commandList)
{

	for each(RenderNode* meshNode in _staticMeshes) {

		RenderParams* params = meshNode->getRenderParams();

		Material* _material = params->getPerNodeParam_MeshMaterial();
		Texture* _texture = params->getPerNodeParam_MeshTexture();
		mesh* _mesh = params->getPerNodeParam_Mesh();
		Transform* transform = params->getPerNodeParam_Transform();

		IShader* _materialShader = _material->getPassList().at(0)->getShader();

		if (params->getPerNodeParam_ForwardRendering()) {

			std::list<RenderNode*> lightNodes = IGraphicsCore::getInstance()->getRenderNodeTree()->queryNodesByType(RENDER_NODE_TYPE::LIGHT_RENDER_NODE);

			std::list<ILight*> pointLights;
			std::list<ILight*> directionalLights;

			for each (RenderNode* node in lightNodes) {
				LightRenderNode* lightNode = (LightRenderNode*)node;

				if (lightNode->getLight()->getType() == LIGHT_TYPE::POINT_LIGHT)
					pointLights.push_back(lightNode->getLight());
				if (lightNode->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT)
					directionalLights.push_back(lightNode->getLight());
			}

			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>(pointLights, _materialShader, true), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);
			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>(directionalLights, _materialShader, true), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);
			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>(params->getGlobalParam_GlobalRenderingCamera(), _materialShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			
			_ioInterface->assignHookResourceByName("index_buffer", _mesh->getIndexBuff());
			_ioInterface->assignHookResourceByName("vertex_buffer", _mesh->getVertexBuff());

			_ioInterface->assignHookResourceByName("color_texture", _texture);

			_materialShader->updateMaterialPassUniforms(_material->getPassList().at(0), _ioInterface);

			commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>(transform, _materialShader),
				GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_materialShader),
				GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_pipelineState->setBlendState(BLEND_STATE::BLENDING_OFF);
			_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			_pipelineState->setRasterState(RASTER_STATE::NORMAL);


			commandList->createCommand(std::make_shared<PipelineSetRasterStateCommand::InitData>(RASTER_STATE::NORMAL),
				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_RASTER_STATE);

			_materialShader->execute(commandList);

			rebuildPSO();

			_pipelineState->applyState(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, _mesh->numIndices),
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
	}
}
