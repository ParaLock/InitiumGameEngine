#include "../include/meshManager.h"

meshManager::meshManager()
{
}


meshManager::~meshManager()
{
}

IResource* meshManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newMesh = new mesh(builder);

	_activeResources->insert({name, newMesh});

	return newMesh;
}
