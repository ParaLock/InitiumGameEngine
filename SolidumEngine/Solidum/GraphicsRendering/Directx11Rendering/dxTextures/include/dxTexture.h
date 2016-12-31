#pragma once
#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"
#include "../../../Textures/include/Texture.h"

class dxTexture : public Texture
{
private:
	ID3D11ShaderResourceView* texture;
public:
	dxTexture();
	~dxTexture();

	void loadImage(LPCWSTR filename);

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);
};

