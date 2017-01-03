#pragma once
#include "../../../GPUPipeline/include/GPUPipeline.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../GraphicsResourcePool/include/GraphicsResourcePoolManagerAccessor.h"

class dxGPUPipeline : public GPUPipeline
{
private:
	void processOp(GPUPipelineOP* op);
public:
	dxGPUPipeline(std::string name);
	~dxGPUPipeline();

	void use();
	void draw(int numIndices);
};

