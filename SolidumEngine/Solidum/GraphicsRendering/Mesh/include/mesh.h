#pragma once

#include "meshLoader.h"
#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../GraphicsBuffers/include/GPUBufferFactory.h"

class mesh
{
private:
	GPUBuffer* _vertexBuff = nullptr;
	GPUBuffer* _indexBuff = nullptr;

	void generateOrthoWindowMesh();
public:
	mesh(LPCWSTR fileName, std::shared_ptr<meshLoader> ldr);
	~mesh();

	int meshSize;
	int indicesSize;

	int numIndices;

	VERTEX *meshVertices;
	DWORD *meshIndices;
	
	GPUBuffer* getVertexBuff() { return _vertexBuff; }
	GPUBuffer* getIndexBuff() { return _indexBuff; }
};
