#include "../include/RenderTargetManager.h"



RenderTargetManager::RenderTargetManager()
{
}


RenderTargetManager::~RenderTargetManager()
{
}

IResource* RenderTargetManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxRenderTarget(builder);
		break;
	}

	if (newResource != nullptr) {
		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}
