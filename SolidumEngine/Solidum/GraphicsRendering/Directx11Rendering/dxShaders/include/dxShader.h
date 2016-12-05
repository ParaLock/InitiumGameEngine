#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../Shaders/include/IShader.h"
#include "../../../GraphicsBuffers/include/GraphicsBufferFactory.h"
#include "../../../RenderTarget/include/RenderTargetFactory.h"
#include "../../../Textures/include/TextureSamplerFactory.h"
#include "../../../Textures/include/ITextureSampler.h"
#include "../../../Textures/include/TextureFactory.h"

#include "../../../../EngineUtils/include/StringManipulation.h"

#include "dxDynamicCBuffer.h"

class dxShader : public IShader
{
private:
	std::map<std::string, dxDynamicCBuffer*> *varNameCBuffMap;

	std::vector<dxDynamicCBuffer*> *cBuffers;

	ID3D11PixelShader *pixelShader;
	ID3D11VertexShader *vertexShader;

	ID3D10Blob *vertexShaderCode, *pixelShaderCode;
	ID3D11InputLayout *InputLayout;

	ITextureSampler *pointTexSampler = NULL;
	ITextureSampler *texSamplerWrap = NULL;

	ITexture *texture = NULL;

	void buildShaderVarIO(LPCWSTR fileName);

public:
	dxShader(LPCWSTR fileName, std::string shaderStageType);
	~dxShader();

	void attachTex(ITexture *tex);

	void updateVar(std::string varName, void *data);

	void updateGPU();

	void Bind();
};

