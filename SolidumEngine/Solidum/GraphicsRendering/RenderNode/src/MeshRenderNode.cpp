#include "../include/MeshRenderNode.h"



MeshRenderNode::MeshRenderNode()
{
	_shader = GraphicsCore::getInstance()->getDefaultShader(DEFAULT_SHADER_TYPE::DEFAULT_MESH);

	_type = RENDER_NODE_TYPE::MESH_RENDER_NODE;
}


MeshRenderNode::~MeshRenderNode()
{
}

void MeshRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;

	isLoaded = true;
}

void MeshRenderNode::unload()
{
	_id = -1;

	isLoaded = false;
}

void MeshRenderNode::updateParameter(std::string varName, void * data)
{
}

void * MeshRenderNode::getParameter(std::string varName)
{
	return nullptr;
}

bool MeshRenderNode::isRenderViable()
{
	if (!_renderParams.getPerNodeParam_isVisible())
		return false;
	if (_renderParams.getPerNodeParam_Mesh() == nullptr)
		return false;
	if (_renderParams.getGlobalParam_GlobalRenderingCamera() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_MeshTexture() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_Transform() == nullptr)
		return false;

	return true;
}

void MeshRenderNode::render()
{
	GraphicsCommandList* commandList = new GraphicsCommandList();

	if (isRenderViable()) {

		Material* _material = _renderParams.getPerNodeParam_MeshMaterial();
		Texture* _texture = _renderParams.getPerNodeParam_MeshTexture();
		mesh* _mesh = _renderParams.getPerNodeParam_Mesh();
		Transform* transform = _renderParams.getPerNodeParam_Transform();

		_shader = _material->getPassList().at(0)->getShader();

		if (_shader->getRenderMode() == SHADER_RENDER_TYPE::FORWARD_RENDERING) {

			std::vector<RenderNode*> lightNodes = GraphicsCore::getInstance()->getRenderNodeTree()->queryAllLights();

			std::list<ILight*> pointLights;
			std::list<ILight*> directionalLights;

			for each (RenderNode* node in lightNodes) {
				LightRenderNode* lightNode = (LightRenderNode*)node;

				if (lightNode->getLight()->getType() == LIGHT_TYPE::POINT_LIGHT)
					pointLights.push_back(lightNode->getLight());
				if (lightNode->getLight()->getType() == LIGHT_TYPE::DIRECTIONAL_LIGHT)
					directionalLights.push_back(lightNode->getLight());
			}

			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>(pointLights, _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);
			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>(directionalLights, _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);
			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			//Hooks must be set in immediate context
			_shader->setMesh(_mesh);
			_shader->setModelTexture(_texture);
			_shader->updateMaterialPassUniforms(_material->getPassList().at(0));

			commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>(transform, _shader), 
				GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_shader), 
				GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
			_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);

			commandList->createCommand(std::make_shared<PipelineSetRasterStateCommand::InitData>(RASTER_STATE::NORMAL), 
				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_RASTER_STATE);

			_shader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>(0, _mesh->numIndices), 
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
		else {

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			_shader->setMesh(_mesh);
			_shader->setModelTexture(_texture);
			_shader->updateMaterialPassUniforms(_material->getPassList().at(0));

			commandList->createCommand(std::make_shared<ShaderUpdateTransformCommand::InitData>
				(transform, _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_TRANSFORM_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_shader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			if (!_renderParams.getPerNodeParam_DepthTestEnableState()) {

				_shader->getPipeline()->setBlendState(BLEND_STATE::ALPHA_BLENDING);
				_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
				_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			}

			_shader->getPipeline()->setBlendState(BLEND_STATE::BLENDING_OFF);
			_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_ENABLE);
			_shader->getPipeline()->setRasterState(RASTER_STATE::NORMAL);

			_shader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, _mesh->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::shared_ptr<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);
}
