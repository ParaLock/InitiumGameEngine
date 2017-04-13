#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode()
{
	_orthoMesh = new mesh();
	_orthoMesh->load(std::make_shared<mesh::InitData>(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_shader = GraphicsCore::getInstance()->getDefaultShader(DEFAULT_SHADER_TYPE::DEFAULT_LIGHT);

	_type = RENDER_NODE_TYPE::LIGHT_RENDER_NODE;
}


LightRenderNode::~LightRenderNode()
{
	delete _orthoMesh;
}

void LightRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;

	isLoaded = true;
}

void LightRenderNode::unload()
{
	isLoaded = false;
}

void LightRenderNode::updateParameter(std::string varName, void * data)
{
}

void * LightRenderNode::getParameter(std::string varName)
{
	if (varName == "IS_SHADOW_CASTER") {

		bool caster = _renderParams.getPerNodeParam_Light()->getIsShadowCaster();

		return (void*)&caster;
	}

	return nullptr;
}

bool LightRenderNode::isRenderViable()
{
	if (!_renderParams.getPerNodeParam_isVisible())
		return false;
	if (_renderParams.getPerNodeParam_Light() == nullptr)
		return false;
	if (_renderParams.getGlobalParam_GlobalRenderingCamera() == nullptr)
		return false;

	return true;
}

void LightRenderNode::render()
{
	GraphicsCommandList* commandList = new GraphicsCommandList();

	if (isRenderViable()) {

		Light* light = _renderParams.getPerNodeParam_Light();

		_shader = ResourceManagerPool::getInstance()->
			getResourceManagerSpecific<LightManager>("LightManager")->getLightShader(light->getType());

		if (_shader->getRenderMode() != SHADER_RENDER_TYPE::FORWARD_RENDERING) {

			//Hooks must be set in immediate context
			_shader->setMesh(_orthoMesh);

			static Matrix4f LprojectionMatrix = light->getProjectionMatrix();
			static Matrix4f LviewMatrix = light->getViewMatrix();
			static Matrix4f LmodelMatrix = light->getModelMatrix();

			static Matrix4f CprojectionMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getProjectionMatrix();
			static Matrix4f CviewMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getViewMatrix();
			static Matrix4f CworldMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getWorldMatrix();
			static Matrix4f CmodelMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getModelMatrix();

			static Matrix4f lightSpaceMatrix = LprojectionMatrix * LviewMatrix;

			lightSpaceMatrix = Matrix4f::transpose(lightSpaceMatrix);

			GraphicsCore* gCore = GraphicsCore::getInstance();
			GraphicsCommandPool* commandPool = gCore->getGraphicsCommandPool();

			GraphicsCommand* camUpdateNode       =	commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);
            GraphicsCommand* updateUniform       =	commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
			GraphicsCommand* updateLightUniforms =  commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);
			GraphicsCommand* syncUniforms        =	commandPool->getResource(GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);
			GraphicsCommand* drawIndexedModel	 =	commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);
			GraphicsCommand* resetPipeline       =	commandPool->getResource(GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);

			syncUniforms->load(std::make_shared<ShaderSyncUniforms::InitData>(_shader));

			camUpdateNode->load(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

			updateLightUniforms->load(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>
				(std::list<ILight*>{light}, _shader));

			updateUniform->load(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightSpaceMatrix", &lightSpaceMatrix), _shader));

			drawIndexedModel->load(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, _orthoMesh->numIndices));

			commandList->queueCommand(camUpdateNode);

			commandList->queueCommand(updateUniform);

			commandList->queueCommand(updateLightUniforms);

			commandList->queueCommand(syncUniforms);

			_shader->execute(commandList);

			commandList->queueCommand(drawIndexedModel);
			commandList->queueCommand(resetPipeline);
		}
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);

}
