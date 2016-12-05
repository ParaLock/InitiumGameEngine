#include "../include/dxDynamicCBuffer.h"



dxDynamicCBuffer::dxDynamicCBuffer(std::string cbuffName)
{
	varList = new std::vector<std::tuple<size_t, size_t>>;

	varMap = new std::map<std::string, std::tuple<size_t, size_t>>;

	name = cbuffName;
}


dxDynamicCBuffer::~dxDynamicCBuffer()
{
	varList->clear();
	delete varList;
	varMap->clear();
	delete varMap;

	if (cbuff != NULL)
		delete[] cbuff;

	if (GPUCBuff != NULL)
		delete GPUCBuff;
}

void dxDynamicCBuffer::addVar(std::string varName, size_t varSize)
{
	if (numVars != 0) {
		varList->push_back(std::make_tuple(varSize, buffLastVarOffset));
		varMap->insert({ varName, std::make_tuple(varSize, buffLastVarOffset) });
		buffLastVarOffset += varSize;
	}
	else {
		varMap->insert({ varName, std::make_tuple(varSize, 0) });
		varList->push_back(std::make_tuple(varSize, 0));		
		buffLastVarOffset += varSize;
	}

	numVars++;
}

std::tuple<size_t, size_t> dxDynamicCBuffer::updateVar(std::string varName, void *data)
{
	std::tuple<size_t, size_t> var = varMap->at(varName);

	size_t varSize = std::get<0>(var);
	size_t varOffset = std::get<1>(var);


	memcpy(static_cast<__int8*>(cbuff) + varOffset, data, varSize);

	return var;
}

void dxDynamicCBuffer::initConstructedCBuffer(int parentShaderType)
{
	GPUCBuff = GraphicsBufferFactory::createBuffer(DXBUFFER_TYPE_SHADER, buffLastVarOffset);

	cbuff = new __int8[buffLastVarOffset];

	ZeroMemory(cbuff, buffLastVarOffset);

	GPUCBuff->parentShaderType = parentShaderType;

	GPUCBuff->Write(cbuff, buffLastVarOffset, 0);
}

void dxDynamicCBuffer::updateGPU()
{
	GPUCBuff->Write(cbuff, buffLastVarOffset, 0);
}

void dxDynamicCBuffer::Bind()
{
	GPUCBuff->Bind();
}
