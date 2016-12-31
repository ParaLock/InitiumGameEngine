#pragma once
#include "../../../GPUPipeline/include/GPUPipeline.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class dxGPUPipeline : public GPUPipeline
{
private:
public:
	dxGPUPipeline();
	~dxGPUPipeline();

	void use();
	void draw(int numIndices);
};

