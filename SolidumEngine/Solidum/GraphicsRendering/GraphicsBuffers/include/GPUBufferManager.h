#pragma once
#include "../../../sysInclude.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxBuffers/include/dxGPUBuffer.h"

#include "GPUBuffer.h"

#include "../../../ResourceManagement/include/IResourceManager.h"

class GPUBufferManager : public IResourceManager
{
public:
	GPUBufferManager();
	~GPUBufferManager();

	IResource* createResource(IResourceBuilder* builder, std::string name);
};

