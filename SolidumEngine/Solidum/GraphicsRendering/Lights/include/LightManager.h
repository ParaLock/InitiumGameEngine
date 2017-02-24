#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "Light.h"

class LightManager : public IResourceManager
{
private:
	std::map<LIGHT_TYPE, Shader*> _lightShaderMap;
public:
	LightManager();
	~LightManager();

	void setLightShader(LIGHT_TYPE light, Shader* shader);
	Shader* getLightShader(LIGHT_TYPE type);

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

