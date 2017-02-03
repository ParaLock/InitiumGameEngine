#include "../include/dxShader.h"

dxShader::dxShader()
{
}


dxShader::~dxShader()
{
}

void dxShader::load(IResourceBuilder * builder)
{
	ShaderBuilder* realBuilder = static_cast<ShaderBuilder*>(builder);

	LPCWSTR shaderFilename = realBuilder->_filename;

	_resManagerPool = realBuilder->_resManagerPool;

	ID3DBlob* errorBlob = nullptr;
	HRESULT result;

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	result = D3DX11CompileFromFile(shaderFilename, 0, 0, "Vshader", "vs_5_0", 0, 0, 0, &vertexShaderCode, &errorBlob, 0);
	if (FAILED(result))
	{
		if (errorBlob)
		{
			std::wstring errorMsg = L"SHADER COMPILE ERROR: ";
			errorMsg += shaderFilename;
			errorMsg += L"\n";
			errorMsg += L"HLSL ERR: ";
			std::string compileErrStr((char*)errorBlob->GetBufferPointer());
			std::wstring tmp;
			tmp.assign(compileErrStr.begin(), compileErrStr.end());
			errorMsg += tmp;


			MessageBox(windowAccessor::hWnd, errorMsg.c_str(), L"ERROR", MB_OK);
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}

	result = dxDev->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
	if (FAILED(result))
	{

		std::wstring errorMsg = L"Vertex SHADER CREATION FAILED: ";
		errorMsg += shaderFilename;
		errorMsg += L"\n";

		MessageBox(windowAccessor::hWnd, errorMsg.c_str(), L"ERROR", MB_OK);

		std::cout << "DX SHADER: VS CREATION FAILED" << std::endl;
	}

	result = D3DX11CompileFromFile(shaderFilename, 0, 0, "Pshader", "ps_5_0", 0, 0, 0, &pixelShaderCode, &errorBlob, 0);
	if (FAILED(result))
	{
		if (errorBlob)
		{
			std::wstring errorMsg = L"SHADER COMPILE ERROR: ";
			errorMsg += shaderFilename;
			errorMsg += L"\n";
			errorMsg += L"HLSL ERR: ";
			std::string compileErrStr((char*)errorBlob->GetBufferPointer());
			std::wstring tmp;
			tmp.assign(compileErrStr.begin(), compileErrStr.end());
			errorMsg += tmp;


			MessageBox(windowAccessor::hWnd, errorMsg.c_str(), L"ERROR", MB_OK);
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());

			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
			errorBlob->Release();
		}
	}


	result = dxDev->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
	if (FAILED(result))
	{
		std::cout << "DX SHADER: PS CREATION FAILED" << std::endl;

		std::wstring errorMsg = L"Pixel SHADER CREATION FAILED: ";
		errorMsg += shaderFilename;
		errorMsg += L"\n";

		MessageBox(windowAccessor::hWnd, errorMsg.c_str(), L"ERROR", MB_OK);
		OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}

	isLoaded = true;
}

void dxShader::unload()
{
	isLoaded = false;
}

void dxShader::attachPipeline(GPUPipeline* pipe)
{
	_pipelineState = pipe;

	enumerateResources(GPUPipelineElementParentShader::SOL_VS, vertexShaderCode);
	enumerateResources(GPUPipelineElementParentShader::SOL_PS, pixelShaderCode);
	
	_constantBufferMemberNameMap = _pipelineState->getVarToBuffMap();
}

void dxShader::enumerateResources(GPUPipelineElementParentShader shaderType, ID3D10Blob *shaderCode)
{
	ID3D11ShaderReflection* pReflector = NULL;
	HRESULT hr = D3DReflect(shaderCode->GetBufferPointer(),
		shaderCode->GetBufferSize(), IID_ID3D11ShaderReflection,
		(void**) &pReflector);

	IResource* newLayout = new dxShaderInputLayout();

	if (!FAILED(hr)) {
		D3D11_SHADER_DESC desc;
		pReflector->GetDesc(&desc);

		for (UINT i = 0; i < desc.InputParameters; i++) {

			D3D11_SIGNATURE_PARAMETER_DESC input_desc;
			pReflector->GetInputParameterDesc(i, &input_desc);

			newLayout->getCore<dxShaderInputLayout>()->addInput(input_desc.ComponentType, input_desc.SemanticName, input_desc.SemanticIndex, input_desc.Mask);
		}

		newLayout->getCore<dxShaderInputLayout>()->generateInputLayout();

		_pipelineState->attachResource(newLayout, "unnamed",
			GPUPipelineElementType::SOL_MESH_DATA_LAYOUT, shaderType, false);

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

				DynamicStructBuilder cbuffBuilder(BufferLayout.Description.Name, true);

				DynamicStruct* cbuff = new DynamicStruct();

				cbuff->load(&cbuffBuilder);

				for (int q = 0; q < BufferLayout.Variables.size(); q++) {
					cbuff->addVariable(BufferLayout.Variables.at(q).Name, BufferLayout.Variables.at(q).Size);
				}

				cbuff->initMemory(_resManagerPool);

				_pipelineState->attachResource(cbuff, BufferLayout.Description.Name,
					GPUPipelineElementType::SOL_GENERAL_DATA_BUFF, shaderType, false);
			}
		}
	}
}

void dxShader::execute(int numIndices)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShader(vertexShader, NULL, 0);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShader(pixelShader, NULL, 0);

	_pipelineState->applyState();

	_pipelineState->executePass(numIndices);
}
