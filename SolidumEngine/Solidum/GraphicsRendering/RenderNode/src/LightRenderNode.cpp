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

			float left, right, top, bottom;

			float screen_width = window::getInstance()->screen_width;
			float screen_height = window::getInstance()->screen_height;

			left = (float)((screen_width / 2) * -1);
			right = left + (float)screen_width;
			top = (float)(screen_height / 2);
			bottom = top - (float)screen_height;

			static Matrix4f LprojectionMatrix = Matrix4f::transpose(light->getProjectionMatrix());
			static Matrix4f LviewMatrix = Matrix4f::transpose(light->getViewMatrix());

			static Matrix4f ShadowMatrix = light->getShadowMatrix();

			static Matrix4f CprojectionMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getProjectionMatrix();
			static Matrix4f CviewMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getViewMatrix();
			static Matrix4f CworldMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getWorldMatrix();
			static Matrix4f CmodelMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getModelMatrix();

			Matrix4f t = Matrix4f::get_identity();

			t[1][1] = 0.5f, t[2][2] = -0.5f, t[3][3] = 1.0f, t[4][1] = 0.5f, t[4][2] = 0.5f, t[4][4] = 1.0f;

			static Matrix4f lightSpaceMatrix = LviewMatrix * LprojectionMatrix;

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightViewMatrix", &LviewMatrix), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(std::make_pair("cbuff_lightProjectionMatrix", &LprojectionMatrix), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);


			commandList->createCommand(std::make_shared<ShaderUpdateLightUniformsCommand::InitData>
				(std::list<ILight*>{light}, _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_LIGHT_UNIFORMS);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_shader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_shader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawIndexedCommand::InitData>
				(0, _orthoMesh->numIndices), GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INDEXED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);

}
