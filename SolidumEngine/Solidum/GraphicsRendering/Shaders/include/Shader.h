#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"
#include "../../GPUPipeline/include/GPUPipelineFactory.h"

class Shader
{
protected:
	GPUPipeline *_pipelineState;
public:
	Shader();
	~Shader();

	void setTexture(Texture *tex);
	void setMeshBuffers(GPUBuffer *indexBuffer, GPUBuffer *vertexBuffer, std::string meshName);

	void updateCPUGeneralDataVar(std::string varName, void * pData);
	void syncGeneralDataVars();

	virtual void performRenderPass(int numIndices);

	virtual void updateGPU();
};

