#include "../include/meshManager.h"

meshManager::meshManager()
{
}


meshManager::~meshManager()
{
}

IResource* meshManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newMesh = new mesh();

	if (loadAsync) {

	}
	else {
		newMesh->load(builder);
	}

	_activeResources->insert({name, newMesh});

	return newMesh;
}
