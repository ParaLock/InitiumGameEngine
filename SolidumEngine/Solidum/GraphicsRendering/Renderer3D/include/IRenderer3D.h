#pragma once

#include "../../Lights/include/Light.h"
#include "../../Mesh/include/mesh.h"
#include "../../../sysInclude.h"

class IRenderer3D
{
public:
	IRenderer3D();
	virtual ~IRenderer3D();

	virtual void clearGBuffers(float R, float G, float B, float A) = 0;

	virtual void setFrameBufferAsCurrent() = 0;

	virtual void clearFrameBuffer(float R, float G, float B, float A) = 0;

	virtual void clearZBuffer() = 0;

	virtual void swapFrame() = 0;
};

