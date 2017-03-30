#include "../include/MeshComponent.h"


MeshComponent::MeshComponent(mesh* mesh, Texture* tex, Material* mat, int index)
{
	_index = index;

	_mesh = mesh;
	_tex = tex;
	_mat = mat;

	setType(COMPONENT_TYPE::MESH_COMPONENT);
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::init()
{
	if (_parent != nullptr) {
		//Static meshes are always index + 1
		_parent->getRenderObject()->addStaticGeometry(_mesh, _index + 1);
		_parent->getRenderObject()->addTexture(_tex, _index + 1);
		_parent->getRenderObject()->addMaterial(_mat, _index + 1);
	}
}

void MeshComponent::update(float delta)
{
	RenderParams params;

	params.setPerNodeParam_Transform(_parent->getTransform());
	params.setPerNodeParam_isVisible(true);
	params.setPerNodeParam_DepthTestEnableState(true);

	if(_parent != nullptr)
		_parent->getRenderObject()->updateRenderNode(RENDER_NODE_TYPE::MESH_RENDER_NODE, _index + 1, params);
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
