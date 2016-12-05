#include "../include/GraphicsBufferFactory.h"



GraphicsBufferFactory::GraphicsBufferFactory()
{
}


GraphicsBufferFactory::~GraphicsBufferFactory()
{
}

IGraphicsBuffer * GraphicsBufferFactory::createBuffer(int buffType, size_t bufferSize)
{

	IGraphicsBuffer *newBuff;

	switch (buffType) {
	case DXBUFFER_TYPE_INDEX:
		newBuff = new dxIndexBuffer(bufferSize);
		break;
	case DXBUFFER_TYPE_SHADER:
		newBuff = new dxShaderBuffer(bufferSize);
		break;
	case DXBUFFER_TYPE_VERTEX:
		newBuff = new dxVertexBuffer(bufferSize);
		break;
	default:
		newBuff = NULL;
		break;
	}

	return newBuff;
}
