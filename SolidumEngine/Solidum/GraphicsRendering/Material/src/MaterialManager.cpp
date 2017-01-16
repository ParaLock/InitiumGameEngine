#include "../include/MaterialManager.h"



MaterialManager::MaterialManager()
{
}


MaterialManager::~MaterialManager()
{
}

IResource* MaterialManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newMesh = new Material(builder);

	_activeResources->insert({ name, newMesh });

	return newMesh;
}
