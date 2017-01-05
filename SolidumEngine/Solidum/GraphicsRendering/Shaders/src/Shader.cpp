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

void Shader::execute(int numIndices)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void Shader::updateUniform(std::string varName, void * pData)
{
	auto itr = _uniformVarNameToBuff->find(varName);

	if (itr != _uniformVarNameToBuff->end()) {

		DynamicBuffer* varsBuff = _uniformVarNameToBuff->at(varName);

		varsBuff->updateVar(varName, pData);
	}
}

void Shader::updateGPU()
{
	DynamicBuffer* previous = nullptr;

	std::vector<DynamicBuffer*> activeGeneralDataBuffers;

	for (auto itr = _uniformVarNameToBuff->begin(); itr != _uniformVarNameToBuff->end(); itr++) {

		if (itr->second != previous)
			activeGeneralDataBuffers.push_back(itr->second);

		previous = itr->second;
	}

	for (unsigned int i = 0; i < activeGeneralDataBuffers.size(); ++i) {
		activeGeneralDataBuffers[i]->updateGPU();
	}
}
