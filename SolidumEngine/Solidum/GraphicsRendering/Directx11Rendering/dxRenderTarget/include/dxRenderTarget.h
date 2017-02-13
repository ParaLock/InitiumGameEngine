#pragma once

#include "../../../../sysInclude.h"

#include "../../../Window/include/windowAccessor.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../RenderTarget/include/RenderTarget.h"

class dxRenderTarget : public RenderTarget
{
private:
	ID3D11Texture2D* _texture = nullptr;
	ID3D11ShaderResourceView* _shaderView = nullptr;
	ID3D11RenderTargetView* _renderTarget = nullptr;

public:
	dxRenderTarget();

	dxRenderTarget(ID3D11RenderTargetView * rt, ID3D11Texture2D * rtTex);
	dxRenderTarget(ID3D11ShaderResourceView * sv, ID3D11Texture2D * svTex);

	~dxRenderTarget();

	void load(IResourceBuilder *builder);
	void unload();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void Clear(float R, float G, float B, float A);
};

