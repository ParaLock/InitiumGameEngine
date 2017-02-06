#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "mesh.h"

class meshManager : public IResourceManager
{
public:
	meshManager();
	~meshManager();
	std::list<std::shared_ptr<std::thread>> resourceLoaders;
	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

