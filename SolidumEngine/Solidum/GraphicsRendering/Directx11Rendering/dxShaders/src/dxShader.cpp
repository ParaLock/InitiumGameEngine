#include "../include/dxShader.h"

dxShader::dxShader()
{
}


dxShader::~dxShader()
{
}

void dxShader::load()
{
	_shaderBindFunc = std::bind(&dxShader::bind, this);

	Shader::InitData* realBuilder = static_cast<Shader::InitData*>(getContext()->getResourceInitParams());

	_genInputLayout = realBuilder->_genInputLayout;

	ID3DBlob* errorBlob;
	HRESULT result;

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	HRESULT compileResult;

	std::string shaderCode = *realBuilder->_shaderCode;

	compileResult = D3DCompile(shaderCode.c_str(), shaderCode.size(),
		0, 0, NULL, "Vshader", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vertexShaderCode, &errorBlob);

	if (FAILED(compileResult)) {
		std::wstring errorMsg = L"SHADER COMPILE ERROR: ";
		errorMsg += L"\n";
		errorMsg += L"HLSL ERR: ";
		std::string compileErrStr((char*)errorBlob->GetBufferPointer());
		std::wstring tmp;
		tmp.assign(compileErrStr.begin(), compileErrStr.end());
		errorMsg += tmp;


		MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);

		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}

	compileResult = D3DCompile(shaderCode.c_str(), shaderCode.size(),
		0, 0, NULL, "Pshader", "ps_5_0", D3DCOMPILE_DEBUG, 0, &pixelShaderCode, &errorBlob);

	if (FAILED(compileResult)) {
		std::wstring errorMsg = L"SHADER COMPILE ERROR: ";
		errorMsg += L"\n";
		errorMsg += L"HLSL ERR: ";
		std::string compileErrStr((char*)errorBlob->GetBufferPointer());
		std::wstring tmp;
		tmp.assign(compileErrStr.begin(), compileErrStr.end());
		errorMsg += tmp;

		MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);

		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		errorBlob->Release();
	}
	
	result = dxDev->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(result))
	{

		std::wstring errorMsg = L"Vertex SHADER CREATION FAILED: ";
		errorMsg += L"\n";

		MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);

		std::cout << "DX SHADER: VS CREATION FAILED" << std::endl;
	}


	result = dxDev->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
	if (FAILED(result))
	{
		std::cout << "DX SHADER: PS CREATION FAILED" << std::endl;

		std::wstring errorMsg = L"Pixel SHADER CREATION FAILED: ";
		errorMsg += L"\n";

		MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}

	enumerateResources(SHADER_TYPE::PIXEL_SHADER, pixelShaderCode, realBuilder->_resCreator);
	enumerateResources(SHADER_TYPE::VERTEX_SHADER, vertexShaderCode, realBuilder->_resCreator);
}

void dxShader::unload()
{
	_constantBufferList.clear();
	_varNameToConstantBuffer.clear();

}

void dxShader::enumerateResources(SHADER_TYPE shaderType, ID3D10Blob *shaderCode, ResourceCreator* resCreator)
{
	ID3D11ShaderReflection* pReflector = NULL;
	HRESULT hr = D3DReflect(shaderCode->GetBufferPointer(),
		shaderCode->GetBufferSize(), IID_ID3D11ShaderReflection,
		(void**) &pReflector);

	ShaderInputLayout* newLayout = new dxShaderInputLayout();
	auto* newdxInputLayout = (dxShaderInputLayout*)newLayout;

	if (!FAILED(hr)) {
		D3D11_SHADER_DESC desc;
		pReflector->GetDesc(&desc);

		for (UINT i = 0; i < desc.InputParameters; i++) {

			D3D11_SIGNATURE_PARAMETER_DESC input_desc;
			pReflector->GetInputParameterDesc(i, &input_desc);

			newdxInputLayout->addInput(input_desc.ComponentType, input_desc.SemanticName, input_desc.SemanticIndex, input_desc.Mask);
		}
		
		if (_genInputLayout) {
			
			newdxInputLayout->generateInputLayout();
		}

		if (shaderType == SHADER_TYPE::VERTEX_SHADER) {

			_vertexInputLayout = newLayout;

		}
		else {
			delete newLayout;
		}

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

				DynamicStruct* cbuff = (DynamicStruct*)resCreator->createResourceImmediate<DynamicStruct>(&DynamicStruct::InitData(BufferLayout.Description.Name, true),
					BufferLayout.Description.Name, [](IResource*) {});

				cbuff->setTargetShader(shaderType);
				_constantBufferList.push_back(cbuff);

				for (int q = 0; q < BufferLayout.Variables.size(); q++) {
					cbuff->addVariable(BufferLayout.Variables.at(q).Name, BufferLayout.Variables.at(q).Size);
					
					_varNameToConstantBuffer.insert({ BufferLayout.Variables.at(q).Name, cbuff });
				}

				cbuff->initMemory(resCreator);
			}
		}
	}
}

void dxShader::bind()
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShader(vertexShader, NULL, 0);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShader(pixelShader, NULL, 0);
}

void dxShader::execute(GraphicsCommandList* commandList)
{
	commandList->createCommand<PipelineBindShaderCommand>
		(&PipelineBindShaderCommand::InitData(this));
}
