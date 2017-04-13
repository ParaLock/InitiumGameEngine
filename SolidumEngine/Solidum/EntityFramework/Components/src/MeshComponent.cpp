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
	if (_parent != nullptr) {

		Transform* transform = _parent->getTransform();

		_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, _index + 1)->
			setPerNodeParam_Transform(_parent->getTransform());

		_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, _index + 1)->
			setPerNodeParam_isVisible(true);

		_parent->getRenderObject()->updateRenderNodeParams(RENDER_NODE_TYPE::MESH_RENDER_NODE, _index + 1)->
			setPerNodeParam_DepthTestEnableState(true);


		int debugPoint = -1;
		
	}
}

void MeshComponent::onEvent(EVENT_PTR evt)
{
}
