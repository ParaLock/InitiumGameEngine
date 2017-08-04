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
	~dxRenderTarget();

	void load();
	void unload();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void Clear(float R, float G, float B, float A);
};

