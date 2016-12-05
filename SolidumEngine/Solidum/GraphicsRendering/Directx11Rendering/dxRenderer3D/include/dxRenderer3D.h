#pragma once

#include "../../../Renderer3D/include/IRenderer3D.h"

#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../dxRenderTarget/include/dxRenderTarget.h"

#include "../../../Lights/include/Light.h"
#include "../../../Mesh/include/mesh.h"

#include "../../../Shaders/include/IShader.h"


class dxRenderer3D : public IRenderer3D
{
private:
	std::vector<IRenderTarget*> *gBuffers;
public:
	dxRenderer3D();
	~dxRenderer3D();

	void RenderLight(Light* light);
	void RenderMesh(mesh* mesh, IShader* shader);

	void addGBuffer(IRenderTarget *gBuff);

	void clearGBuffers(float R, float G, float B, float A);

	void setGBuffers(std::string gBuffUsageContext);

	void setFrameBufferAsCurrent();

	void clearFrameBuffer(float R, float G, float B, float A);

	void clearZBuffer();

	void swapFrame();
};

