#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBufferFactory.h"

class ShaderGeneralDataVar {
private:
	size_t _size;
	size_t _startAddr;
	size_t _endAddr;

public:
	ShaderGeneralDataVar(size_t size, size_t startAddr, size_t endAddr) {
		_size = size;
		_startAddr = startAddr;
		_endAddr = endAddr;
	}

	size_t getSize() { return _size; }
	size_t getStartAddr() { return _startAddr; };
	size_t getEndAddr() { return _endAddr; };
};

class ShaderGeneralDataBuffer
{
private:
	std::string _name;

	std::map<std::string, ShaderGeneralDataVar*> *_variableMap;
	std::map<std::string, size_t> *_typeSizeMap;

	void *_pBuffCPUMem = nullptr;
	int _lastVarOffset = 0;

	int numVars = 0;

	GPUBuffer *_GPUBuff = nullptr;
public:
	ShaderGeneralDataBuffer(std::string name);
	~ShaderGeneralDataBuffer();

	void registerVarType(std::string typeName, size_t typeSize);

	void addVariable(std::string varName, std::string varType);

	void updateVar(std::string varName, void *pData);

	void initMemory();
	void updateGPU();

	std::string getName() { return _name; };

	GPUBuffer* getGPUBuffer() { return _GPUBuff; };
	std::vector<std::string> getVarNameList();
};

