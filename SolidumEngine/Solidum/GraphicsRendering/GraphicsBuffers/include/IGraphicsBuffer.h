#pragma once

class IGraphicsBuffer
{
public:
	IGraphicsBuffer();
	virtual ~IGraphicsBuffer();

	virtual void Read(void *pDest, size_t byteToRead, size_t offset) = 0;
	virtual void Write(void *pSrc, size_t byteToWrite, size_t offset) = 0;

	int resSlot = 0;
	int parentShaderType = 0;

	virtual size_t GetBuffSize() = 0;

	virtual void Bind() = 0;
};

