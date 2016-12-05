#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../GraphicsBuffers/include/IGraphicsBuffer.h"

class dxShaderBuffer : public IGraphicsBuffer
{
private:

	ID3D11Buffer* bufferPtr;
	const unsigned long buffSize;

public:
	dxShaderBuffer(unsigned long bufferSize);
	~dxShaderBuffer();

	void Write(void *pSrc, size_t byteToWrite, size_t offset);
	void Read(void *pDest, size_t byteToRead, size_t offset);

	void Bind();

	size_t GetBuffSize() { return buffSize; };

	ID3D11Buffer *GetBuff() { return bufferPtr; };
};
