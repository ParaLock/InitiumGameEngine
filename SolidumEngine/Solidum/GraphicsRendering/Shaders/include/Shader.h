#pragma once
#include "../../../sysInclude.h"
#include "../../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"
#include "../../../GraphicsRendering/GPUPipeline/include/GPUPipeline.h"
#include "../../GPUPipeline/include/GPUPipelineFactory.h"

class Shader
{
protected:
	std::map<std::string, DynamicBuffer*> *_uniformVarNameToBuff;

	GPUPipeline *_pipelineState;
public:
	Shader();
	~Shader();

	void setTexture(Texture *tex);
	void setMeshBuffers(GPUBuffer *indexBuffer, GPUBuffer *vertexBuffer, std::string meshName);

	void updateUniform(std::string varName, void * pData);
	void updateGPU();

	virtual void execute(int numIndices);
};

