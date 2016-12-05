#pragma once

#include "Light.h"

#include "../../Shaders/include/ShaderFactory.h"

enum LIGHT_TYPES {
	LIGHT_TYPE_DIRECTIONAL = 0x1,
	LIGHT_TYPE_POINT = 0x2
};

class LightFactory {
private:
	static std::map<std::string, Light*> *lightLibrary;

	static std::map<LIGHT_TYPES, std::string> *lightShaderHash;
public:
	LightFactory();
	~LightFactory();

	static Light* createLight(LIGHT_TYPES lightType, std::string ID);

	static Light* requestLight(std::string ID);

	static void registerShaderToLight(LIGHT_TYPES light, std::string shaderName);

	static void destroyLightLibrary();
};