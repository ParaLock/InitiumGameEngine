#pragma once

#include "../common.h"

class IGPUBuffer {
public:

	virtual void Write(void *pSrc, size_t byteToWrite, size_t offset) = 0;
	virtual void Read(void *pDest, size_t byteToRead, size_t offset) = 0;

	virtual void swapInternalBuffer(void *pNewBuff) = 0;

	virtual size_t getSize() = 0;

	virtual BUFFER_TYPE getBuffType() = 0;
private:
};