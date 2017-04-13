#pragma once
#include "../../../sysInclude.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "mesh.h"

class meshManager : public IResourceManager
{
public:
	meshManager();
	~meshManager();

	IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

