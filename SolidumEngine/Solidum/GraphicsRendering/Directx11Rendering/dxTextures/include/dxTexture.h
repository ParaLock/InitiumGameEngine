#pragma once
#include "../../../../sysInclude.h"

#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../Textures/include/ITexture.h"

class dxTexture : public ITexture
{
private:
	ID3D11ShaderResourceView* texture;
public:
	dxTexture(LPCWSTR fileName);
	~dxTexture();

	ID3D11ShaderResourceView* GetTexShaderView() { return texture; };

	void Bind();
};

