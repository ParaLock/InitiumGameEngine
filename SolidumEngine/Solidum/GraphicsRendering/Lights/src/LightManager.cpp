#include "../include/LightManager.h"



LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

IResource* LightManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newLight = new Light(builder);

	_activeResources->insert({ name, newLight });

	return newLight;
}
