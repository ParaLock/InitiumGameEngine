#pragma once
#include "../../../DepthStencil/include/DepthStencil.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class dxDepthStencil : public DepthStencil
{
private:
	ID3D11Texture2D* _depthTexture;
	ID3D11ShaderResourceView* _depthShaderView;
	ID3D11DepthStencilView* _depthStencil;
public:
	dxDepthStencil();
	~dxDepthStencil();

	void clear(float depth);

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void* getParameter(std::string varName);
};

