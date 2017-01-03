#include "../include/dxShader.h"

dxShader::dxShader(LPCWSTR shaderFilename, LPCWSTR pipelineFilename)
{
	ID3DBlob* errorBlob = nullptr;
	HRESULT result;

	_pipelineState = GPUPipelineFactory::createPipeline(pipelineFilename);

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	result = D3DX11CompileFromFile(shaderFilename, 0, 0, "Vshader", "vs_5_0", 0, 0, 0, &vertexShaderCode, &errorBlob, 0);
	if (FAILED(result))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			return;
		}
	}

	result = dxDev->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(result))
	{
		std::cout << "DX SHADER: VS CREATION FAILED" << std::endl;
		return;
	}

	enumerateResources(GPUPipelineElementParentShader::SOL_VS, vertexShaderCode);

	result = D3DX11CompileFromFile(shaderFilename, 0, 0, "Pshader", "ps_5_0", 0, 0, 0, &pixelShaderCode, &errorBlob, 0);
	if (FAILED(result))
	{
		if (errorBlob)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
			return;
		}
	}


	result = dxDev->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
	if (FAILED(result))
	{
		std::cout << "DX SHADER: PS CREATION FAILED" << std::endl;
		return;
	}

	enumerateResources(GPUPipelineElementParentShader::SOL_PS, pixelShaderCode);
}


dxShader::~dxShader()
{
}

void dxShader::enumerateResources(GPUPipelineElementParentShader shaderType, ID3D10Blob *shaderCode)
{
	ID3D11ShaderReflection* pReflector = NULL;
	HRESULT hr = D3DReflect(shaderCode->GetBufferPointer(),
		shaderCode->GetBufferSize(), IID_ID3D11ShaderReflection,
		(void**) &pReflector);

	ShaderInputLayout* newLayout = new dxShaderInputLayout();

	if (!FAILED(hr)) {
		D3D11_SHADER_DESC desc;
		pReflector->GetDesc(&desc);

		for (UINT i = 0; i < desc.InputParameters; i++) {

			D3D11_SIGNATURE_PARAMETER_DESC input_desc;
			pReflector->GetInputParameterDesc(i, &input_desc);

			newLayout->addInput(input_desc.ComponentType, input_desc.SemanticName, input_desc.SemanticIndex, input_desc.Mask);
		}
		newLayout->generateInputLayout();

		_pipelineState->attachShaderInputLayout(newLayout, "");

		for (UINT i = 0; i < desc.OutputParameters; i++) {

			D3D11_SIGNATURE_PARAMETER_DESC input_desc;
			pReflector->GetOutputParameterDesc(i, &input_desc);
		}

		for (UINT i = 0; i < desc.ConstantBuffers; i++) {
			dxConstantBufferLayout BufferLayout;

			ID3D11ShaderReflectionConstantBuffer* pConstBuffer = 
				pReflector->GetConstantBufferByIndex(i);
			pConstBuffer->GetDesc(&BufferLayout.Description);

			for (UINT j = 0; j < BufferLayout.Description.Variables; j++) {
				ID3D11ShaderReflectionVariable* pVariable = 
					pConstBuffer->GetVariableByIndex(j);
				D3D11_SHADER_VARIABLE_DESC var_desc;
				pVariable->GetDesc(&var_desc);

				BufferLayout.Variables.push_back(var_desc);

				ID3D11ShaderReflectionType* pType = pVariable->GetType();
				D3D11_SHADER_TYPE_DESC type_desc;

				pType->GetDesc(&type_desc);
				
				BufferLayout.Types.push_back(type_desc);
			}

			if (BufferLayout.Description.Type == D3D11_CT_CBUFFER) {

				DynamicBuffer *cbuff = new DynamicBuffer(BufferLayout.Description.Name, true);

				for (int q = 0; q < BufferLayout.Variables.size(); q++) {
					cbuff->addVariable(BufferLayout.Variables.at(q).Name, BufferLayout.Variables.at(q).Size);
				}

				cbuff->initMemory();

				_pipelineState->attachGeneralShaderDataBuffer(cbuff, shaderType);
			}
		}
	}
}

GPUPipeline * dxShader::generatePipeline()
{
	return nullptr;
}

void dxShader::performRenderPass(int numIndices)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShader(vertexShader, NULL, 0);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShader(pixelShader, NULL, 0);

	_pipelineState->use();

	_pipelineState->draw(numIndices);
}

void dxShader::updateGPU()
{

}
