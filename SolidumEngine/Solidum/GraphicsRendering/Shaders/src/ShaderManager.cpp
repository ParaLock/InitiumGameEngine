#include "../include/ShaderManager.h"



ShaderManager::ShaderManager()
{
}


ShaderManager::~ShaderManager()
{
}

IResource* ShaderManager::createResource(IResourceBuilder * builder, std::string name)
{
	IResource* newResource = nullptr;

	switch (ActiveGraphicsAPI::getCurrentAPI()) {
	case SUPPORTED_GRAPHICS_API::DIRECTX11:
		newResource = new dxShader(builder);
		break;
	}

	if (newResource != nullptr) {

		addResource(newResource, name);

		return newResource;
	}

	return nullptr;
}
