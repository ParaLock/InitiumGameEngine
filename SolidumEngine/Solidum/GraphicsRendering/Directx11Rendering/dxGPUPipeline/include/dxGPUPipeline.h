#pragma once
#include "../../../GPUPipeline/include/GPUPipeline.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class dxGPUPipeline : public GPUPipeline
{
private:
	void processOp(GPUPipelineOP* op);
public:
	dxGPUPipeline();
	~dxGPUPipeline();

	void use();
	void draw(int numIndices);
};

