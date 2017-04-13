#include "../include/ShaderManager.h"



ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

IResource* ShaderManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxShader();
		break;
	}

	if (loadAsync) {

	}
	else {
		newResource->load(builder);
	}

	if (newResource != nullptr) {

		addResource(newResource, name);

		return newResource;
	}

	return nullptr;
}
