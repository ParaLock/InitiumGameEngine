#pragma once
#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../../EngineUtils/include/HelperFunctions.h"
#include "../../../GraphicsBuffers/include/GPUBuffer.h"

class dxGPUBuffer : public GPUBuffer
{
private:
	ID3D11Buffer* bufferPtr;
public:
	dxGPUBuffer(size_t size, BUFFER_TYPE type, BUFFER_CPU_ACCESS access);
	~dxGPUBuffer();

	void Write(void *pSrc, size_t byteToWrite, size_t offset);
	void Read(void *pDest, size_t byteToRead, size_t offset);

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void swapInternalBuffer(void *pNewBuff);
};

