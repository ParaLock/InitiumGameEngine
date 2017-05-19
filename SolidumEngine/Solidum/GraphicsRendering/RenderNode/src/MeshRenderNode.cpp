#include "../include/MeshRenderNode.h"



MeshRenderNode::MeshRenderNode()
{
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
	_parent = nullptr;
	_child = nullptr;

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
	_renderParams.setPerNodeParam_isVisible(true);
}
