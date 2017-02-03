#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "mesh.h"

class meshManager : public IResourceManager
{
public:
	meshManager();
	~meshManager();

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

