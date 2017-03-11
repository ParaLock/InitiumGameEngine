#pragma once

#include "../../../../sysInclude.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

#include "../../../../EngineUtils/include/StringManipulation.h"

#include "../../../GPUPipeline/include/GPUPipeline.h"

#include "../../../Shaders/include/Shader.h"

#include "../../../../EngineUtils/include/DynamicStruct.h"

#include "dxShaderInputLayout.h"

struct dxConstantBufferLayout {
	D3D11_SHADER_BUFFER_DESC Description;
	std::vector<D3D11_SHADER_VARIABLE_DESC> Variables;
	std::vector<D3D11_SHADER_TYPE_DESC> Types;
};


class dxShader : public Shader
{
private:
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;

	ID3D10Blob *vertexShaderCode, *pixelShaderCode;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
public:
	dxShader();
	~dxShader();

	void load(IResourceBuilder* builder);
	void unload();

	void attachPipeline(GPUPipeline* pipe);

	void enumerateResources(SHADER_TYPE shaderType, ID3D10Blob *shaderCode);

	void bind();

	void execute(int numIndices);
};

