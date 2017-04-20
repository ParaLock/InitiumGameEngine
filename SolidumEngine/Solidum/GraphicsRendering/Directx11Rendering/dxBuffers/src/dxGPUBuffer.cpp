#include "../include/dxGPUBuffer.h"



dxGPUBuffer::dxGPUBuffer()
{
}


dxGPUBuffer::~dxGPUBuffer()
{
}

void dxGPUBuffer::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData *realBuilder = static_cast<InitData*>(builder.get());

	_size = realBuilder->_size;
	_type = realBuilder->_type;
	_access = realBuilder->_access;

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT result;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	switch (_access) {
	case BUFFER_CPU_ACCESS::CPU_ACCESS_READ:
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		break;
	case BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE:
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case BUFFER_CPU_ACCESS::CPU_ACCESS_READWRITE:
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	switch (_type) {
	case BUFFER_TYPE::VERTEX_BUFF:
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		break;
	case BUFFER_TYPE::INDEX_BUFF:
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		break;
	case BUFFER_TYPE::SHADER_BUFF:
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		break;
	}

	//if (_type == BUFFER_TYPE::SHADER_BUFF && !(16 % _size) == 0) {

	//	std::wstring errorMsg = L"DX CBUFFER ERROR: Padding in-correct: ";

	//	MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);
	//	return;
	//}

	bd.ByteWidth = _size;

	bd.Usage = D3D11_USAGE_DYNAMIC;

	result = dxDev->CreateBuffer(&bd, NULL, &bufferPtr);

	isLoaded = true;
}

void dxGPUBuffer::unload()
{
	isLoaded = false;
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
	if (varName == "BUFFER") {
		bufferPtr = (ID3D11Buffer*)data;
	}
}

void * dxGPUBuffer::getParameter(std::string varName)
{
	if (varName == "BUFFER") {
		return bufferPtr;
	}

	return nullptr;
}

void dxGPUBuffer::swapInternalBuffer(void * pNewBuff)
{
	//TEST FUNCTION... Yup, it sucks.
	ID3D11Buffer* newBuff = (ID3D11Buffer*)pNewBuff;

	bufferPtr = newBuff;
}

