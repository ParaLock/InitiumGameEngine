#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "Light.h"

class LightManager : public IResourceManager
{
public:
	LightManager();
	~LightManager();

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

