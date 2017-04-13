#include "../include/TextureSamplerManager.h"



TextureSamplerManager::TextureSamplerManager()
{
}


TextureSamplerManager::~TextureSamplerManager()
{
}

IResource* TextureSamplerManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxTextureSampleState();
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

	return nullptr;
}
