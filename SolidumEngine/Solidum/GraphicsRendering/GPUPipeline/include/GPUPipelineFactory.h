#pragma once
#include "../../../sysInclude.h"
#include "../../../EngineUtils/include/StringManipulation.h"
#include "../../GraphicsResourcePool/include/GraphicsResourcePoolManagerAccessor.h"
#include "GPUPipeline.h"

#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

#include "../../RenderTarget/include/RenderTargetFactory.h"
#include "../../Textures/include/TextureFactory.h"
#include "../../Textures/include/TextureSamplerFactory.h"
#include "../../GraphicsBuffers/include/GPUBufferFactory.h"

#include "../../Directx11Rendering/dxGPUPipeline/include/dxGPUPipeline.h"

#include "../../Directx11Rendering/dxShaders/include/dxShaderInputLayout.h"

class GPUPipelineFactory
{
private:

public:
	GPUPipelineFactory();
	~GPUPipelineFactory();

	static GPUPipeline *createPipeline(LPCWSTR pipelineDescFile);
};

