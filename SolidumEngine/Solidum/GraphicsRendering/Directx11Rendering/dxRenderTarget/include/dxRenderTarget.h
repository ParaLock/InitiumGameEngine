#pragma once

#include "../../../../sysInclude.h"

#include "../../../Window/include/windowAccessor.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../RenderTarget/include/IRenderTarget.h"

class dxRenderTarget : public IRenderTarget
{
private:
	ID3D11Texture2D* texture = NULL;
	ID3D11ShaderResourceView* shaderView = NULL;
	ID3D11RenderTargetView* renderTarget = NULL;

public:
	dxRenderTarget();
	~dxRenderTarget();

	ID3D11Texture2D* GetTexture() { return texture; };
	ID3D11ShaderResourceView* GetShaderView() { return shaderView; };
	ID3D11RenderTargetView* GetRenderTarget() { return renderTarget; };

	void BindAsShaderResource();

	void Clear(float R, float G, float B, float A);
};

