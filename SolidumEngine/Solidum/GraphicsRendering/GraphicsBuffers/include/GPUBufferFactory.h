#pragma once
#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxBuffers/include/dxGPUBuffer.h"
#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

class GPUBufferFactory
{
private:
public:
	GPUBufferFactory();
	~GPUBufferFactory();

	static GPUBuffer* createBuffer(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access);
};

