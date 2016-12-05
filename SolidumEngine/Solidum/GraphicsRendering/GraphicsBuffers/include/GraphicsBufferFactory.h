#pragma once

#include "IGraphicsBuffer.h"

#include "../../Directx11Rendering/dxBuffers/include/dxIndexBuffer.h"
#include "../../Directx11Rendering/dxBuffers/include/dxShaderBuffer.h"
#include "../../Directx11Rendering/dxBuffers/include/dxVertexBuffer.h"

#define DXBUFFER_TYPE_VERTEX 0x0
#define DXBUFFER_TYPE_INDEX 0x1
#define DXBUFFER_TYPE_SHADER 0x2

#define NULL_ARG 0x0

class GraphicsBufferFactory
{
public:
	GraphicsBufferFactory();
	~GraphicsBufferFactory();

	static IGraphicsBuffer* createBuffer(int buffType, size_t bufferSize);
};

