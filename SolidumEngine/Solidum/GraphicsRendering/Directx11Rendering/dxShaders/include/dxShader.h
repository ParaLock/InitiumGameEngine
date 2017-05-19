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


//class HLSLIncludeHandler : public ID3D10Include
//{
//public:
//	HLSLIncludeHandler(std::string& shaderCode)
//		: _shaderCode(shaderCode) {}
//	~HLSLIncludeHandler() {}
//
//	STDMETHOD(Open)(D3D10_INCLUDE_TYPE IncludeType,
//		LPCSTR pFileName,
//		LPCVOID pParentData,
//		LPCVOID *ppData,
//		UINT *pByteLen
//		)
//	{
//		std::string source = _shaderCode;
//
//		*pByteLen = static_cast<UINT>(source.length());
//		char* pChar = new char[*pByteLen];
//		memcpy(pChar, source.c_str(), *pByteLen);
//		*ppData = pChar;
//
//		return S_OK;
//	}
//
//	STDMETHOD(Close)(LPCVOID pData)
//	{
//		char* pChar = (char*)pData;
//		delete[] pChar;
//		return S_OK;
//	}
//protected:
//	std::string& _shaderCode;
//};

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

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void enumerateResources(SHADER_TYPE shaderType, ID3D10Blob *shaderCode);

	void bind();

	void execute(GraphicsCommandList* commandList);
};

