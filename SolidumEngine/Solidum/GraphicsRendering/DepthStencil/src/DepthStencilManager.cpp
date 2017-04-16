#include "../include/DepthStencilManager.h"



DepthStencilManager::DepthStencilManager()
{
}


DepthStencilManager::~DepthStencilManager()
{
}

IResource * DepthStencilManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:

		newResource = new dxDepthStencil();
		break;
	}

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	_activeResources->insert({ name, newResource });

	return newResource;
}
