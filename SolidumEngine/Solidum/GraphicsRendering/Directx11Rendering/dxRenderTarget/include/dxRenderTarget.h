#pragma once

#include "../../../../sysInclude.h"

#include "../../../Window/include/window.h"
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

	dxRenderTarget(ID3D11RenderTargetView * rt, ID3D11Texture2D * rtTex, Viewport& view);
	dxRenderTarget(ID3D11ShaderResourceView * sv, ID3D11Texture2D * svTex, Viewport& view);

	~dxRenderTarget();

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void Clear(float R, float G, float B, float A);
};

