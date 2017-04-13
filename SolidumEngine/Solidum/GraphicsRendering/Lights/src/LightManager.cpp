#include "../include/LightManager.h"



LightManager::LightManager()
{
}


LightManager::~LightManager()
{
}

void LightManager::setLightShader(LIGHT_TYPE light, Shader * shader)
{
	_lightShaderMap[light] = shader;
}

Shader * LightManager::getLightShader(LIGHT_TYPE type)
{
	return _lightShaderMap.at(type);
}

IResource* LightManager::createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync)
{
	IResource* newLight = new Light();

	if (loadAsync) {

	}
	else {
		newLight->load(builder);
	}

	_activeResources->insert({ name, newLight });

	return newLight;
}
