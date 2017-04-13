#pragma once
#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../GraphicsBuffers/include/GPUBuffer.h"

class dxGPUBuffer : public GPUBuffer
{
private:
	ID3D11Buffer* bufferPtr;
public:
	dxGPUBuffer();
	~dxGPUBuffer();

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void Write(void *pSrc, size_t byteToWrite, size_t offset);
	void Read(void *pDest, size_t byteToRead, size_t offset);

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void swapInternalBuffer(void *pNewBuff);
};


