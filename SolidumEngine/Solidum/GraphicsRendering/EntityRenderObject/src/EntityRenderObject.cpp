#include "../include/EntityRenderObject.h"



EntityRenderObject::EntityRenderObject()
{
}


EntityRenderObject::~EntityRenderObject()
{
}

void EntityRenderObject::addLightComponent(LightComponent * lightComponent, int index)
{
	if (_renderResources.find( std::type_index(typeid(LightComponent))) == _renderResources.end()) {
		_renderResources.insert({ std::type_index(typeid(LightComponent)), std::map<int, Component*>() });
	}

	_renderResources.at(typeid(LightComponent)).insert({index, lightComponent});
}

void EntityRenderObject::addMeshComponent(MeshComponent * meshComponent, int index)
{
	if (_renderResources.find(std::type_index(typeid(MeshComponent))) == _renderResources.end()) {
		_renderResources.insert({ std::type_index(typeid(MeshComponent)), std::map<int, Component*>() });
	}

	_renderResources.at(std::type_index(typeid(MeshComponent))).insert({ index, meshComponent });
}

void EntityRenderObject::setMeshTexture(Texture * tex, int index)
{
	if (_renderResources.find(std::type_index(typeid(MeshComponent))) == _renderResources.end()) {
		return;
	}

	MeshComponent* comp = (MeshComponent*)_renderResources.at(std::type_index(typeid(MeshComponent))).at(index);

	comp->setTexture(tex);
}

void EntityRenderObject::setMeshMaterial(Material * mat, int index)
{
	if (_renderResources.find(std::type_index(typeid(MeshComponent))) == _renderResources.end()) {
		return;
	}

	MeshComponent* comp = (MeshComponent*)_renderResources.at(std::type_index(typeid(MeshComponent))).at(index);

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

			innerItr->second->AddRenderData(datagroup);

			innerItr++;
		}

		itr++;
	}

	for each(Component* comp in _uniqueRenderResources) {

		comp->AddRenderData(datagroup);

	}
}
