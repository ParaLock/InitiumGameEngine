#include "../include/dxVertexBuffer.h"


dxVertexBuffer::dxVertexBuffer(unsigned long bufferSize) :
	buffSize(bufferSize)
{
	dxDevice *dxCore = dxDeviceAccessor::dxEncapsulator;

	HRESULT result;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = buffSize;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	result = dxCore->dxDev->CreateBuffer(&bd, NULL, &bufferPtr);
}

dxVertexBuffer::~dxVertexBuffer()
{
	bufferPtr->Release();

}

void dxVertexBuffer::Write(void *pSrc, size_t byteToWrite, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	ZeroMemory(&ms, sizeof(ms));

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(static_cast<__int8*>(ms.pData) + offset, pSrc, byteToWrite);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxVertexBuffer::Read(void *pDest, size_t byteToRead, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_READ_WRITE, NULL, &ms);

	memcpy(pDest, static_cast<__int8*>(ms.pData) + offset, byteToRead);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxVertexBuffer::Bind()
{
	UINT offset = 0;
	UINT stride = sizeof(VERTEX);

	dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetVertexBuffers(0, 1, &bufferPtr, &stride, &offset);
}
