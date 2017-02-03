#include "../include/LightManager.h"



LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

IResource* LightManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newLight = new Light();

	if (loadAsync) {

	}
	else {
		newLight->load(builder);
	}

	_activeResources->insert({ name, newLight });

	return newLight;
}
