#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::setTexture(Texture * tex)
{
	_pipelineState->setPrimaryTexture(tex);
}

void Shader::setMeshBuffers(GPUBuffer * indexBuffer, GPUBuffer * vertexBuffer, std::string meshName)
{
	_pipelineState->setVertexBuffer(vertexBuffer);
	_pipelineState->setIndexBuffer(indexBuffer);
}

void Shader::updateCPUGeneralDataVar(std::string varName, void * pData)
{
	_pipelineState->updateCPUGeneralDataVar(varName, pData);
}

void Shader::syncGeneralDataVars()
{
	_pipelineState->syncGeneralDataVars();
}

void Shader::performRenderPass(int numIndices)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void Shader::updateGPU()
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}
