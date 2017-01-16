#pragma once
#include "../../../sysInclude.h"
#include "../../../EngineUtils/include/StringManipulation.h"
#include "../../Directx11Rendering/dxGPUPipeline/include/dxGPUPipeline.h"
#include "../../Directx11Rendering/dxShaders/include/dxShaderInputLayout.h"

#include "../../../ResourceManagement/include/IResourceManager.h"

#include "GPUPipeline.h"

#include "../../ActiveGraphicsAPI.h"


class GPUPipelineFactory
{
private:

public:
	GPUPipelineFactory();
	~GPUPipelineFactory();

	static GPUPipeline *createPipeline(IResourceBuilder* builder);
};

