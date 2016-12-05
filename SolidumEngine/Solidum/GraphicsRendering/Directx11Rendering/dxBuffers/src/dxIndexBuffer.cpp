#include "../include/dxIndexBuffer.h"


dxIndexBuffer::dxIndexBuffer(unsigned long bufferSize) :
	buffSize(bufferSize)
{
	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT result;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = buffSize;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	result = dxDev->CreateBuffer(&bd, NULL, &bufferPtr);
}


dxIndexBuffer::~dxIndexBuffer()
{
	bufferPtr->Release();
}

void dxIndexBuffer::Write(void *pSrc, size_t byteToWrite, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	ZeroMemory(&ms, sizeof(ms));

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(static_cast<__int8*>(ms.pData) + offset, pSrc, byteToWrite);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxIndexBuffer::Read(void *pDest, size_t byteToRead, size_t offset)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_READ_WRITE, NULL, &ms);

	memcpy(pDest, static_cast<__int8*>(ms.pData) + offset, byteToRead);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxIndexBuffer::Bind()
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetIndexBuffer(bufferPtr, DXGI_FORMAT_R32_UINT, 0);
}


