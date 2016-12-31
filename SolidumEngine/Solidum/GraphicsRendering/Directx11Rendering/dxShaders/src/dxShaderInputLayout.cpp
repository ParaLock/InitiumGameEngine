#include "..\include\dxShaderInputLayout.h"



dxShaderInputLayout::dxShaderInputLayout(std::string name)
{
	_inputLayoutElementList = new std::list<std::pair<std::string, std::string>>;
	_name = name;
}


dxShaderInputLayout::~dxShaderInputLayout()
{
	delete _inputLayoutElementList;
}

void dxShaderInputLayout::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_INPUT_LAYOUT") {
		_inputLayout = (ID3D11InputLayout*)data;
	}
}

void * dxShaderInputLayout::getParameter(std::string varName)
{
	if (varName == "D3D_INPUT_LAYOUT") {
		return _inputLayout;
	}
	return nullptr;
}

void dxShaderInputLayout::generateInputLayout()
{
	int elementCount = 0;

	std::string inputElements = "";

	std::string elementName;
	std::string elementSemantic;
	std::string elementType;

	D3D11_INPUT_ELEMENT_DESC *inputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[_inputLayoutElementList->size()];

	for (std::list<std::pair<std::string, std::string>>::iterator itr 
		= _inputLayoutElementList->begin(); itr != _inputLayoutElementList->end(); itr++) 
	{
		elementName = itr->second;

		std::transform(itr->second.begin(), itr->second.end(), itr->second.begin(), ::toupper);
		
		elementSemantic = itr->second;

		if (elementCount == 0) {
			inputLayoutDesc[elementCount].AlignedByteOffset = 0;
		}
		else {
			inputLayoutDesc[elementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		}

		inputLayoutDesc[elementCount].SemanticName = itr->second.c_str();
		
		inputLayoutDesc[elementCount].InputSlot = 0;
		inputLayoutDesc[elementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesc[elementCount].SemanticIndex = 0;
		inputLayoutDesc[elementCount].InstanceDataStepRate = 0;

		if (itr->first == "FLOAT3") {
			inputLayoutDesc[elementCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			elementType = "float3";

			_dataStride += sizeof(float[3]);
		}
		if (itr->first == "FLOAT2") {
			inputLayoutDesc[elementCount].Format = DXGI_FORMAT_R32G32_FLOAT;
			elementType = "float2";

			_dataStride += sizeof(float[2]);
		}
		if (itr->first == "FLOAT4") {
			inputLayoutDesc[elementCount].Format = DXGI_FORMAT_R32G32B32_FLOAT;
			elementType = "float4";

			_dataStride += sizeof(float[3]);
		}

		inputElements += elementType + " " + elementName + " : " + elementSemantic + "; ";

		elementCount++;
	}

	ID3D11VertexShader *vertexShader;
	ID3D10Blob *vertexShaderCode;

	ID3D10Blob *compileError;

	std::string dumbyShaderStr =
		"struct VertexInputType"
		"{"
		+ inputElements +
		"};"
		
		"struct PixelInputType"
		"{"
		""
		""
		""
		"};"

		"PixelInputType Vshader(VertexInputType input)"
		"{"
		"	PixelInputType output;"
		"	return output;"
		"}";

	std::wstring wsTmp(dumbyShaderStr.begin(), dumbyShaderStr.end());

	OutputDebugStringW(wsTmp.c_str());

	inputLayoutDesc[2].Format;

	HRESULT compileResult;
	HRESULT vCreateResult;
	HRESULT ILCreateResult;

	compileResult = D3DCompile(dumbyShaderStr.c_str(), dumbyShaderStr.size(),
		NULL, 0, 0, "Vshader", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vertexShaderCode, &compileError);

	vCreateResult = dxDeviceAccessor::dxEncapsulator->dxDev->
		CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);

	ILCreateResult = dxDeviceAccessor::dxEncapsulator->dxDev->
		CreateInputLayout(inputLayoutDesc, elementCount, vertexShaderCode->GetBufferPointer(),
			vertexShaderCode->GetBufferSize(), &_inputLayout);
}
