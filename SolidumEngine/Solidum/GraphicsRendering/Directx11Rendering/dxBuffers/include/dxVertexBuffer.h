#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../GraphicsBuffers/include/IGraphicsBuffer.h"

struct VERTEX;

class dxVertexBuffer : public IGraphicsBuffer
{
private:

	ID3D11Buffer* bufferPtr;
	const unsigned long buffSize;

public:
	dxVertexBuffer(unsigned long bufferSize);
	~dxVertexBuffer();

	void Write(void *pSrc, size_t byteToWrite, size_t offset);
	void Read(void *pDest, size_t byteToRead, size_t offset);

	void Bind();

	size_t GetBuffSize() { return buffSize; };

	ID3D11Buffer* GetBuff() { return bufferPtr; };
};
