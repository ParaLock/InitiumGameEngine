#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode(uint64_t id)
{
	_id = id;

	_orthoMesh = new mesh();
	_orthoMesh->load(&meshBuilder(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_shader = GraphicsCore::getInstance()->getDefaultShader(DEFAULT_SHADER_TYPE::DEFAULT_LIGHT);

	_type = RENDER_NODE_TYPE::LIGHT_RENDER_NODE;
}


LightRenderNode::~LightRenderNode()
{
	delete _orthoMesh;
}

bool LightRenderNode::isRenderViable()
{
	if (!_renderParams.getPerNodeParam_isVisible())
		return false;
	if (_renderParams.getPerNodeParam_Light() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_Mesh() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_RenderCamera() == nullptr)
		return false;

	return true;
}

void * LightRenderNode::getVar(std::string varname)
{
	if (varname == "IS_SHADOW_CASTER") {

		bool caster = _renderParams.getPerNodeParam_Light()->getIsShadowCaster();

		return (void*)&caster;
	}

	return nullptr;
}

void LightRenderNode::render()
{
	if (isRenderViable()) {

		_isVisible = _renderParams.getPerNodeParam_isVisible();

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

			static Matrix4f CviewProj = Matrix4f::transpose(CviewMatrix * CprojectionMatrix);

			static Matrix4f LviewProj = Matrix4f::transpose(LviewMatrix * LprojectionMatrix);

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateCameraUniformsCommand(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateUniformCommand(&CviewProj, "cbuff_camViewProj", _shader));
		
			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateUniformCommand(&LviewProj, "cbuff_lightViewProj", _shader));
			
			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderSyncUniforms(_shader));

			GCQManager::getInstance()->getPrimaryCommandQueue()->queueCommand(
				new ShaderUpdateLightUniformsCommand(std::vector<ILight*>{light}, _shader));


			_shader->execute(_orthoMesh->numIndices);
		}
	}
}
