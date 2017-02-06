#include "../include/RenderProcessManager.h"



RenderProcessManager::RenderProcessManager()
{
}


RenderProcessManager::~RenderProcessManager()
{
}

IResource * RenderProcessManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newResource = new RenderProcess();

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	if (newResource != nullptr) {

		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}
