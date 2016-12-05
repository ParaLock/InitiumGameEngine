#pragma once

#include "../../RenderTarget/include/IRenderTarget.h"
#include "../../Lights/include/Light.h"
#include "../../Shaders/include/IShader.h"

#include "../../Mesh/include/mesh.h"

#include "../../../sysInclude.h"

class IRenderer3D
{
public:
	IRenderer3D();
	virtual ~IRenderer3D();

	virtual void RenderLight(Light* light) = 0;
	virtual void RenderMesh(mesh* mesh, IShader* shader) = 0;

	virtual void addGBuffer(IRenderTarget *gBuff) = 0;

	virtual void clearGBuffers(float R, float G, float B, float A) = 0;

	virtual void setGBuffers(std::string gBuffUsageContext) = 0;

	virtual void setFrameBufferAsCurrent() = 0;

	virtual void clearFrameBuffer(float R, float G, float B, float A) = 0;

	virtual void clearZBuffer() = 0;

	virtual void swapFrame() = 0;
};

