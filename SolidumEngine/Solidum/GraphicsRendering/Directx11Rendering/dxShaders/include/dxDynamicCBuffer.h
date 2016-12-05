#pragma once

#include "../../../../sysInclude.h"

#include "../../../GraphicsBuffers/include/IGraphicsBuffer.h"
#include "../../../GraphicsBuffers/include/GraphicsBufferFactory.h"

class dxDynamicCBuffer
{
private:

	std::map<std::string, std::tuple<size_t, size_t>> *varMap;

	std::vector<std::tuple<size_t, size_t>> *varList;

	void *cbuff = NULL;

	int buffLastVarOffset = 0;

	int numVars = 0;

	std::string name;

	IGraphicsBuffer* GPUCBuff = NULL;

public:
	dxDynamicCBuffer(std::string cbuffName);
	~dxDynamicCBuffer();

	void addVar(std::string varName, size_t varSize);

	std::tuple<size_t, size_t> updateVar(std::string varName, void *data);

	void initConstructedCBuffer(int parentShaderType);

	void updateGPU();

	void Bind();
};

