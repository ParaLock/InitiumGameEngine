#pragma once
#include "RenderProcess.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

#include "../../ActiveGraphicsAPI.h"

class RenderProcessManager : public IResourceManager
{
public:
	RenderProcessManager();
	~RenderProcessManager();

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

