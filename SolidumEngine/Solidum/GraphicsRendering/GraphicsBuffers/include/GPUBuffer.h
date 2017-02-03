#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"
#include "../../../ResourceFramework/include/IResourceManager.h"

class GPUBufferBuilder : public IResourceBuilder {
public:
	size_t _size;
	BUFFER_TYPE _type;
	BUFFER_CPU_ACCESS _access;

	GPUBufferBuilder(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access) {
		_size = size;
		_type = type;
		_access = access;
	}
};


class GPUBuffer : public IResource
{
protected:
	size_t _size;
	BUFFER_TYPE _type;
	BUFFER_CPU_ACCESS _access;

public:
	GPUBuffer();
	~GPUBuffer();

	virtual void load(IResourceBuilder* builder) = 0;
	virtual void unload() = 0;

	virtual void Write(void *pSrc, size_t byteToWrite, size_t offset) = 0;
	virtual void Read(void *pDest, size_t byteToRead, size_t offset) = 0;

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void swapInternalBuffer(void *pNewBuff) = 0;

	BUFFER_TYPE getBuffType() { return _type; };
};

