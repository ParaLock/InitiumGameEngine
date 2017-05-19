#include "../include/SkyBoxRenderNode.h"


SkyBoxRenderNode::SkyBoxRenderNode()
{
	_type = RENDER_NODE_TYPE::SKYBOX_WEATHER_RENDER_NODE;

	_wvp = Matrix4f::get_identity();
}

SkyBoxRenderNode::~SkyBoxRenderNode()
{
}

void SkyBoxRenderNode::load(std::shared_ptr<IResourceBuilder> builder)
{
	_wvp = Matrix4f::get_identity();

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_id = realBuilder->_id;

	_skydomeApexColor = realBuilder->_apexColor;
	_skydomeCenterColor = realBuilder->_centerColor;

	isLoaded = true;
}

void SkyBoxRenderNode::unload()
{
	_parent = nullptr;
	_child = nullptr;


	isLoaded = false;
}

bool SkyBoxRenderNode::isRenderViable()
{
	if (!_renderParams.getPerNodeParam_isVisible())
		return false;
	if (_renderParams.getPerNodeParam_Mesh() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_RenderCamera() == nullptr)
		return false;
	if (_renderParams.getPerNodeParam_MeshTexture() == nullptr)
		return false;

	return true;
}

void SkyBoxRenderNode::render()
{
	_renderParams.setPerNodeParam_isVisible(true);
}
