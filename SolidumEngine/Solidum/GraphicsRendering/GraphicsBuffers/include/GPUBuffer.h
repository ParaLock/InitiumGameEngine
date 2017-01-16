#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceManagement/include/IResource.h"
#include "../../../ResourceManagement/include/IResourceBuilder.h"
#include "../../../ResourceManagement/include/IResourceManager.h"

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

	virtual void Write(void *pSrc, size_t byteToWrite, size_t offset);
	virtual void Read(void *pDest, size_t byteToRead, size_t offset);

	virtual void updateParameter(std::string varName, void *data);
	virtual void* getParameter(std::string varName);

	virtual void swapInternalBuffer(void *pNewBuff);

	BUFFER_TYPE getBuffType() { return _type; };
};

