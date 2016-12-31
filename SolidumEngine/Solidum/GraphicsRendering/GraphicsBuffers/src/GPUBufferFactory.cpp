#include "../include/GPUBufferFactory.h"



GPUBufferFactory::GPUBufferFactory()
{
}


GPUBufferFactory::~GPUBufferFactory()
{
}

GPUBuffer* GPUBufferFactory::createBuffer(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access)
{
	GPUBuffer* newBuff;

	switch (ActiveAPITypeAccessor::_apiInUse) {
		case DIRECTX11:
			newBuff = new dxGPUBuffer(size, type, access);
		break;
	}

	return newBuff;
}
