#pragma once
#include "../../sysInclude.h"
#include "../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"

#include "../../ResourceManagement/include/IResource.h"

#include "../../ResourceManagement/include/ResourceManagerPool.h"

class DynamicBufferMember {
private:
	size_t _size;
	size_t _startAddr;
	size_t _endAddr;
	
public:
	DynamicBufferMember(size_t size, size_t startAddr, size_t endAddr) {
		_size = size;
		_startAddr = startAddr;
		_endAddr = endAddr;
	}

	size_t getSize() { return _size; }
	size_t getStartAddr() { return _startAddr; };
	size_t getEndAddr() { return _endAddr; };
};

class DynamicBuffer : public IResource
{
private:
	std::string _name;

	bool _hasGPUBuff = false;

	std::map<std::string, DynamicBufferMember*> *_variableMap;
	std::map<std::string, size_t> *_typeSizeMap;

	void *_pBuffCPUMem = nullptr;
	int _lastVarOffset = 0;

	int numVars = 0;

	GPUBuffer* _GPUBuff = nullptr;

public:
	DynamicBuffer(std::string name, bool hasGPUBuff);
	~DynamicBuffer();

	void addVariable(std::string varName, size_t varSize);

	void updateVar(std::string varName, void *pData);

	void updateGPU();

	void initMemory(ResourceManagerPool* resManagerPool);

	std::string getName() { return _name; };
	std::vector<std::string> getVarNameList();

	GPUBuffer* getGPUBuffer() { return _GPUBuff; };
};

