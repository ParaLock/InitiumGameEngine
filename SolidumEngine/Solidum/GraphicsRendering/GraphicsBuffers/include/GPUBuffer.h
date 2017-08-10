#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/Resource.h"
#include "../../../ResourceFramework/include/ResourceContext.h"
#include "../../../../SolidumAPI/core_objects/include/ResourceInitParams.h"

#include "../include/GPUBufferFactory.h"

class GPUBufferFactory;
class ResourcePool;

class GPUBuffer : public Resource<GPUBuffer, GPUBufferFactory, ResourcePool>
{
public:
	GPUBuffer();
	~GPUBuffer();

	struct InitData : public ResourceInitParams {

		InitData() {}

		size_t _size;
		BUFFER_TYPE _type;
		BUFFER_CPU_ACCESS _access;

		InitData(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access) {

			_size = size;
			_type = type;
			
			_access = access;
		}
	};

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void Write(void *pSrc, size_t byteToWrite, size_t offset) = 0;
	virtual void Read(void *pDest, size_t byteToRead, size_t offset) = 0;

	virtual void swapInternalBuffer(void *pNewBuff) = 0;

	size_t getSize() { return _size; }

	BUFFER_TYPE getBuffType() { return _type; };

protected:
	size_t _size;
	BUFFER_TYPE _type;
	BUFFER_CPU_ACCESS _access;
};

