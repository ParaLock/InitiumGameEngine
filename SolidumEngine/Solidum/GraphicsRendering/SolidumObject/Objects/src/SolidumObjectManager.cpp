#include "../include/SolidumObjectManager.h"



SolidumObjectManager::SolidumObjectManager()
{
}


SolidumObjectManager::~SolidumObjectManager()
{

}

IResource * SolidumObjectManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* solidumObject = new SolidumObject(builder);

	_activeResources->insert({ name, solidumObject });

	return solidumObject;
}
