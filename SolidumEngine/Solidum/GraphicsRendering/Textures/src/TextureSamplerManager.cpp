#include "../include/TextureSamplerManager.h"



TextureSamplerManager::TextureSamplerManager()
{
}


TextureSamplerManager::~TextureSamplerManager()
{
}

IResource* TextureSamplerManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxTextureSampleState(builder);
		break;
	}

	if (newResource != nullptr) {
		_activeResources->insert({ name, newResource });

		return newResource;
	}

	return nullptr;
}
