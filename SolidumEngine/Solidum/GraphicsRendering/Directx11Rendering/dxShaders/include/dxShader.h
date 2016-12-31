#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../../EngineUtils/include/StringManipulation.h"

#include "../../../GPUPipeline/include/GPUPipeline.h"

#include "../../../Shaders/include/Shader.h"

class dxShader : public Shader
{
private:

	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;

	ID3D10Blob *vertexShaderCode, *pixelShaderCode;
public:
	dxShader(LPCWSTR shaderFilename, LPCWSTR pipelineDescFilename);
	~dxShader();

	void performRenderPass(int numIndices);

	void updateGPU();
};

