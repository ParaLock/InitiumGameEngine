#include "../include/meshManager.h"

meshManager::meshManager()
{
}


meshManager::~meshManager()
{
}

IResource* meshManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
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
