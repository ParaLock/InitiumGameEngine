#pragma once

#include "../../../Renderer3D/include/IRenderer3D.h"

#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../dxRenderTarget/include/dxRenderTarget.h"

#include "../../../Lights/include/Light.h"
#include "../../../Mesh/include/mesh.h"


class dxRenderer3D : public IRenderer3D
{
private:
public:
	dxRenderer3D();
	~dxRenderer3D();

	void setFrameBufferAsCurrent();

	void clearFrameBuffer(float R, float G, float B, float A);

	void clearZBuffer();

	void swapFrame();
};

