#include "../include/LightRenderNode.h"



LightRenderNode::LightRenderNode()
{
	_type = RENDER_NODE_TYPE::LIGHT_RENDER_NODE;
}


LightRenderNode::~LightRenderNode()
{
}

void LightRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;

	isLoaded = true;
}

void LightRenderNode::unload()
{
	_parent = nullptr;
	_child = nullptr;


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
	if (_renderParams.getPerNodeParam_Transform() == nullptr)
		return false;

	return true;
}

void LightRenderNode::render()
{
	_renderParams.setPerNodeParam_isVisible(true);
}
