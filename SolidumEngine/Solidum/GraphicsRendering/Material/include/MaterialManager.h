#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "Material.h"

class MaterialManager : public IResourceManager
{
public:
	MaterialManager();
	~MaterialManager();

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

