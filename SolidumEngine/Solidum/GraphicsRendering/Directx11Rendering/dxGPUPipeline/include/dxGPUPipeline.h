#pragma once
#include "../../../GPUPipeline/include/GPUPipeline.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class dxGPUPipeline : public GPUPipeline
{
private:
	void processOp(GPUPipelineOP* op);
public:
	dxGPUPipeline(ResourceManagerPool* managerPool);
	~dxGPUPipeline();

	void applyState();
	void executePass(int numIndices);
};

