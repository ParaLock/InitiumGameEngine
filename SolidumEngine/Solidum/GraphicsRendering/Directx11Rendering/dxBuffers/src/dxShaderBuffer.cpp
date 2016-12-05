#include "../include/dxShaderBuffer.h"


dxShaderBuffer::dxShaderBuffer(unsigned long bufferSize) :
	buffSize(bufferSize)
{
	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	D3D11_BUFFER_DESC cBufferDesc;

	ZeroMemory(&cBufferDesc, sizeof(cBufferDesc));

	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.ByteWidth = bufferSize;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;
	cBufferDesc.StructureByteStride = 0;

	dxDev->CreateBuffer(&cBufferDesc, NULL, &bufferPtr);
}

dxShaderBuffer::~dxShaderBuffer()
{
	bufferPtr->Release();
}

void dxShaderBuffer::Write(void *pSrc, size_t byteToWrite, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	memcpy(static_cast<__int8*>(ms.pData) + offset, pSrc, byteToWrite);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxShaderBuffer::Read(void *pDest, size_t byteToRead, size_t offset)
{
	ID3D11DeviceContext *dxDevContext = dxDeviceAccessor::dxEncapsulator->dxDevContext;

	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE ms;

	result = dxDevContext->Map(bufferPtr, NULL, D3D11_MAP_READ_WRITE, NULL, &ms);

	memcpy(pDest, static_cast<__int8*>(ms.pData) + offset, byteToRead);

	dxDevContext->Unmap(bufferPtr, NULL);
}

void dxShaderBuffer::Bind()
{
	switch (parentShaderType) {
	case PARENT_SHADER_TYPE_PIXEL:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetConstantBuffers(resSlot, 1, &bufferPtr);
		break;
	case PARENT_SHADER_TYPE_VERTEX:
		dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetConstantBuffers(resSlot, 1, &bufferPtr);
		break;
	default:
		break;
	}
}
