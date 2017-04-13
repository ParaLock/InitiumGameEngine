#include "../include/MaterialManager.h"



MaterialManager::MaterialManager()
{
}


MaterialManager::~MaterialManager()
{
}

IResource* MaterialManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
{
	IResource* newMat = new Material();

	if (loadAsync) {

	}
	else {
		newMat->load(builder);
	}

	_activeResources->insert({ name, newMat });

	return newMat;
}
