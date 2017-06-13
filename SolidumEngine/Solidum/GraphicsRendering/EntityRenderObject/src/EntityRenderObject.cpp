#include "../include/EntityRenderObject.h"



EntityRenderObject::EntityRenderObject()
{
}


EntityRenderObject::~EntityRenderObject()
{
}

void EntityRenderObject::addLightComponent(LightComponent * lightComponent, int index)
{
	if (_renderResources.find(COMPONENT_TYPE::LIGHT_COMPONENT) == _renderResources.end()) {
		_renderResources.insert({ COMPONENT_TYPE::LIGHT_COMPONENT, std::map<int, Component*>() });
	}

	_renderResources.at(COMPONENT_TYPE::LIGHT_COMPONENT).insert({index, lightComponent});
}

void EntityRenderObject::addMeshComponent(MeshComponent * meshComponent, int index)
{
	if (_renderResources.find(COMPONENT_TYPE::MESH_COMPONENT) == _renderResources.end()) {
		_renderResources.insert({ COMPONENT_TYPE::MESH_COMPONENT, std::map<int, Component*>() });
	}

	_renderResources.at(COMPONENT_TYPE::MESH_COMPONENT).insert({ index, meshComponent });
}

void EntityRenderObject::setMeshTexture(Texture * tex, int index)
{
	if (_renderResources.find(COMPONENT_TYPE::MESH_COMPONENT) == _renderResources.end()) {
		return;
	}

	MeshComponent* comp = (MeshComponent*)_renderResources.at(COMPONENT_TYPE::MESH_COMPONENT).at(index);

	comp->setTexture(tex);
}

void EntityRenderObject::setMeshMaterial(Material * mat, int index)
{
	if (_renderResources.find(COMPONENT_TYPE::MESH_COMPONENT) == _renderResources.end()) {
		return;
	}

	MeshComponent* comp = (MeshComponent*)_renderResources.at(COMPONENT_TYPE::MESH_COMPONENT).at(index);

	comp->setMaterial(mat);
}

void EntityRenderObject::addUniqueComponent(Component* comp)
{
	_uniqueRenderResources.push_back(comp);
}

void EntityRenderObject::attachRenderDataToGroup(RenderDataGroup * datagroup)
{
	auto& itr = _renderResources.begin();

	while (itr != _renderResources.end()) {

		auto& innerMap = itr->second;

		auto& innerItr = innerMap.begin();

		while (innerItr != innerMap.end()) {

			datagroup->addPacketToRenderGroup(innerItr->second->createRenderData());

			innerItr++;
		}

		itr++;
	}

	for each(Component* comp in _uniqueRenderResources) {
		datagroup->addPacketToRenderGroup(comp->createRenderData());
	}
}
