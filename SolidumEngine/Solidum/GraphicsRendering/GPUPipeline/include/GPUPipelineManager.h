#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "GPUPipeline.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

class GPUPipelineManager : public IResourceManager
{
public:
	GPUPipelineManager();
	~GPUPipelineManager();

	IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

