#include "../include/GPUBuffer.h"



GPUBuffer::GPUBuffer()
{
}


GPUBuffer::~GPUBuffer()
{
}

void GPUBuffer::Write(void * pSrc, size_t byteToWrite, size_t offset)
{
	std::cout << "GPU BUFFER: NO GRAPHICS API DIRECTIVE DETECTED";
}

void GPUBuffer::Read(void * pDest, size_t byteToRead, size_t offset)
{
	std::cout << "GPU BUFFER: NO GRAPHICS API DIRECTIVE DETECTED";
}

void GPUBuffer::updateParameter(std::string varName, void * data)
{
	std::cout << "GPU BUFFER: NO GRAPHICS API DIRECTIVE DETECTED";
}

void * GPUBuffer::getParameter(std::string varName)
{
	std::cout << "GPU BUFFER: NO GRAPHICS API DIRECTIVE DETECTED";
	return nullptr;
}

void GPUBuffer::swapInternalBuffer(void * pNewBuff)
{
	std::cout << "GPU BUFFER: NO GRAPHICS API DIRECTIVE DETECTED";
}
