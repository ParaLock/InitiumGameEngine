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

	std::function<void()> _shaderBindFunc;

	bool _genInputLayout = false;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };
public:
	dxShader();
	~dxShader();

	void load();
	void unload();

	void enumerateResources(SHADER_TYPE shaderType, ID3D10Blob *shaderCode, ResourceCreator* resCreator);

	void bind();

	void execute(GraphicsCommandList* commandList);
};

