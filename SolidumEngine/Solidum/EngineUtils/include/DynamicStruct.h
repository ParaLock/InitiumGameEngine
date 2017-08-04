#pragma once
#include "../../sysInclude.h"
#include "../../GraphicsRendering/GraphicsBuffers/include/GPUBuffer.h"

#include "../../ResourceFramework/include/Resource.h"

#include "../../ResourceFramework/include/ResourceInitParams.h"

#include "../../ResourceFramework/include/ResourceCreator.h"

#include "../../ResourceFramework/include/GenericFactory.h"

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

class ResourcePool;

class DynamicStruct : public Resource<DynamicStruct, GenericFactory, ResourcePool>
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

	static const unsigned int TYPE = 0;

	struct InitData : public ResourceInitParams {

		InitData() {}

		

		std::string _name;
		bool _hasGPUBuff;

		InitData(std::string name, bool hasGPUBuff) {
			_name = name;
			_hasGPUBuff = hasGPUBuff;
		}
	};

	void load();
	void unload();

	void addVariable(std::string varName, size_t varSize);

	void updateVar(std::string varName, void *pData);

	void updateGPU();

	void initMemory(ResourceCreator* resCreator);

	std::string getName() { return _name; };
	std::vector<std::string> getVarNameList();

	GPUBuffer* getGPUBuffer() { return _GPUBuff; };

protected:
};

