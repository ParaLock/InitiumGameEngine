#pragma once
#include "../../sysInclude.h"
#include "../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"

#include "../../ResourceFramework/include/IResource.h"

#include "../../ResourceFramework/include/IResourceBuilder.h"

#include "../../ResourceFramework/include/ResourceManagerPool.h"

class DynamicStructMember {
private:
	size_t _size;
	size_t _startAddr;
	size_t _endAddr;
	
public:
	DynamicStructMember(size_t size, size_t startAddr, size_t endAddr) {
		_size = size;
		_startAddr = startAddr;
		_endAddr = endAddr;
	}

	size_t getSize() { return _size; }
	size_t getStartAddr() { return _startAddr; };
	size_t getEndAddr() { return _endAddr; };
};

class DynamicStruct : public IResource
{
private:
	std::string _name;

	bool _hasGPUBuff = false;

	std::map<std::string, DynamicStructMember*> *_variableMap;
	std::map<std::string, size_t> *_typeSizeMap;

	void *_pBuffCPUMem = nullptr;
	int _lastVarOffset = 0;

	int numVars = 0;

	GPUBuffer* _GPUBuff = nullptr;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName);

public:
	DynamicStruct();
	~DynamicStruct();

	struct InitData : public IResourceBuilder {
		std::string _name;
		bool _hasGPUBuff;

		InitData(std::string name, bool hasGPUBuff) {
			_name = name;
			_hasGPUBuff = hasGPUBuff;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void addVariable(std::string varName, size_t varSize);

	void updateVar(std::string varName, void *pData);

	void updateGPU();

	void initMemory();

	std::string getName() { return _name; };
	std::vector<std::string> getVarNameList();

	GPUBuffer* getGPUBuffer() { return _GPUBuff; };
};

