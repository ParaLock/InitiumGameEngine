#include "../include/dxGPUBuffer.h"



dxGPUBuffer::dxGPUBuffer(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access)
{
	_size = size;
	_type = type;
	_access = access;

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT result;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	switch (_access) {
		case CPU_ACCESS_READ:
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
			break;
		case CPU_ACCESS_WRITE:
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;
		case CPU_ACCESS_READWRITE:
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
	}

	switch (_type) {
		case VERTEX_BUFF:
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
		case INDEX_BUFF:
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
		case SHADER_BUFF:
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}

	bd.ByteWidth = _size;

	bd.Usage = D3D11_USAGE_DYNAMIC;

	result = dxDev->CreateBuffer(&bd, NULL, &bufferPtr);
}


dxGPUBuffer::~dxGPUBuffer()
{
}

void dxGPUBuffer::Write(void *pSrc, size_t byteToWrite, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	ZeroMemory(&ms, sizeof(ms));

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(static_cast<__int8*>(ms.pData) + offset, pSrc, byteToWrite);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxGPUBuffer::Read(void *pDest, size_t byteToRead, size_t offset)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_READ_WRITE, NULL, &ms);

	memcpy(pDest, static_cast<__int8*>(ms.pData) + offset, byteToRead);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxGPUBuffer::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_BUFFER") {
		bufferPtr = (ID3D11Buffer*)data;
	}
}

void * dxGPUBuffer::getParameter(std::string varName)
{
	if (varName == "D3D_BUFFER") {
		return bufferPtr;
	}

	return nullptr;
}

void dxGPUBuffer::swapInternalBuffer(void * pNewBuff)
{
	//TEST FUNCTION... I know it sucks.
	ID3D11Buffer* newBuff = (ID3D11Buffer*)pNewBuff;

	bufferPtr = newBuff;
}

