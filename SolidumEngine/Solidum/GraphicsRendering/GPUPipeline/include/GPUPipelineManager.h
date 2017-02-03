#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxGPUPipeline/include/dxGPUPipeline.h"

#include "GPUPipeline.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

class GPUPipelineManager : public IResourceManager
{
public:
	GPUPipelineManager();
	~GPUPipelineManager();

	IResource* createResource(IResourceBuilder* builder, std::string name, bool loadAsync);
};

