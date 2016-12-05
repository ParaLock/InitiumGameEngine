#include "..\include\LightFactory.h"

LightFactory::LightFactory()
{
}

LightFactory::~LightFactory()
{
}

std::map<std::string, Light*>* LightFactory::lightLibrary = new std::map<std::string, Light*>;

std::map<LIGHT_TYPES, std::string>* LightFactory::lightShaderHash = new std::map<LIGHT_TYPES, std::string>;

Light * LightFactory::createLight(LIGHT_TYPES lightType, std::string ID)
{
	Light* newLight;

	switch (lightType) {
	case LIGHT_TYPE_DIRECTIONAL:
		newLight = new Light(ShaderFactory::requestShader(lightShaderHash->at(LIGHT_TYPE_DIRECTIONAL)));
		break;
	case LIGHT_TYPE_POINT:
		newLight = new Light(ShaderFactory::requestShader(lightShaderHash->at(LIGHT_TYPE_POINT)));
		break;
	}

	lightLibrary->insert({ID, newLight});

	return newLight;
}

Light * LightFactory::requestLight(std::string ID)
{
	return lightLibrary->at(ID);
}

void LightFactory::registerShaderToLight(LIGHT_TYPES light, std::string shaderName)
{
	lightShaderHash->insert({ light, shaderName });
}

void LightFactory::destroyLightLibrary()
{
	lightShaderHash->clear();
	delete lightShaderHash;

	for (std::map<std::string, Light*>::iterator itr = lightLibrary->begin(); itr != lightLibrary->end(); itr++) {
		Light *lightToRemove = itr->second;

		delete lightToRemove;
	}

	lightLibrary->clear();
	delete lightLibrary;
}
