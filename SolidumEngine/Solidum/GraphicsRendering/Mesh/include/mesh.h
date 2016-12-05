#pragma once

#include "meshLoader.h"

#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../GraphicsBuffers/include/GraphicsBufferFactory.h"

#include "../../Shaders/include/IShader.h"

class mesh
{
private:
	IGraphicsBuffer *indexBuff;
	IGraphicsBuffer *vertexBuff;

public:
	mesh(LPCWSTR fileName, std::shared_ptr<meshLoader> ldr);
	~mesh();

	void draw();

	int meshSize;
	int indicesSize;

	int numIndices;

	VERTEX *meshVertices;
	DWORD *meshIndices;
};
