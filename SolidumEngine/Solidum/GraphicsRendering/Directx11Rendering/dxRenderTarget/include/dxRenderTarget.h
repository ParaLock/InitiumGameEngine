#pragma once

#include "../../../../sysInclude.h"

#include "../../../Window/include/windowAccessor.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../RenderTarget/include/RenderTarget.h"

class dxRenderTarget : public RenderTarget
{
private:
	ID3D11Texture2D* texture = NULL;
	ID3D11ShaderResourceView* shaderView = NULL;
	ID3D11RenderTargetView* renderTarget = NULL;

public:
	dxRenderTarget(int mipLevel, int aaSamples, TEX_FORMAT texFormat);
	~dxRenderTarget();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void Clear(float R, float G, float B, float A);
};

