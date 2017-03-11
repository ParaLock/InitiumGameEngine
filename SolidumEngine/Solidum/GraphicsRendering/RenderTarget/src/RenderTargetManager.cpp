#include "../include/RenderTargetManager.h"



RenderTargetManager::RenderTargetManager()
{
}


RenderTargetManager::~RenderTargetManager()
{
}

IResource* RenderTargetManager::createResource(IResourceBuilder * builder, std::string name, bool loadAsync)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxRenderTarget();
		break;
	}

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	if (newResource != nullptr) {
		_activeResources->insert({ name, newResource });

		return newResource;
	}

	int debugRef = -1;

	return nullptr;
}
