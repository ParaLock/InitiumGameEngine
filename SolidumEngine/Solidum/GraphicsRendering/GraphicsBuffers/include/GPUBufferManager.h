#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxBuffers/include/dxGPUBuffer.h"

#include "GPUBuffer.h"

#include "../../../ResourceFramework/include/IResourceManager.h"

class GPUBufferManager : public IResourceManager
{
public:
	GPUBufferManager();
	~GPUBufferManager();

	IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync);
};

