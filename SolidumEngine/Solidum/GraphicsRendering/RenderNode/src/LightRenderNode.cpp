#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode(Light* light, uint64_t id) :
	_light(light)
{
	_id = id;

	_orthoMesh = new mesh();
	_orthoMesh->load(&meshBuilder(L"gen_ortho_window_mesh", ResourceManagerPool::getInstance()));

	_shader = ResourceManagerPool::getInstance()->getResourceManagerSpecific<LightManager>
		("LightManager")->getLightShader(_light->getType());

	_light->setIsShadowCaster(true);

	_type = RENDER_NODE_TYPE::LIGHT_RENDER_NODE;
}


LightRenderNode::~LightRenderNode()
{
	delete _orthoMesh;
}

void * LightRenderNode::getVar(std::string varname)
{
	if (varname == "IS_SHADOW_CASTER") {

		bool caster = _light->getIsShadowCaster();

		return (void*)&caster;
	}

	return nullptr;
}

void LightRenderNode::render()
{
	_isVisible = _renderParams.getPerNodeParam_isVisible();

	if (_isVisible) {

		if (_shader->getRenderMode() != SHADER_RENDER_TYPE::FORWARD_RENDERING) {

			//Hooks must be set in immediate context
			_shader->setMesh(_orthoMesh);

			static Matrix4f LprojectionMatrix = _light->getProjectionMatrix();
			static Matrix4f LviewMatrix = _light->getViewMatrix();
			static Matrix4f LmodelMatrix = _light->getModelMatrix();

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
				new ShaderUpdateLightUniformsCommand(std::vector<ILight*>{_light}, _shader));


			_shader->execute(_orthoMesh->numIndices);
		}

		_isVisible = false;
	}
}
