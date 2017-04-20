#include "..\include\dxShaderInputLayout.h"



dxShaderInputLayout::dxShaderInputLayout()
{
	_inputLayoutElementList = new std::vector<ShaderInputLayoutElement*>;
	inputLayoutDesc = nullptr;
	//_name = name;
}


dxShaderInputLayout::~dxShaderInputLayout()
{
	for (int i = 0; i < _inputLayoutElementList->size(); i++) {
		delete _inputLayoutElementList->operator[](i);
	}

	delete _inputLayoutElementList;
}


void dxShaderInputLayout::updateParameter(std::string varName, void * data)
{
	if (varName == "INPUT_LAYOUT") {
		_inputLayout = (ID3D11InputLayout*)data;
	}
}

void * dxShaderInputLayout::getParameter(std::string varName)
{
	if (varName == "INPUT_LAYOUT") {
		return _inputLayout;
	}
	return nullptr;
}

void dxShaderInputLayout::addInput(int type, std::string name, UINT index, BYTE mask)
{
	ShaderInputLayoutElement *newElement = new ShaderInputLayoutElement(name, type, index, mask);

	_inputLayoutElementList->push_back(newElement);
}

void dxShaderInputLayout::generateInputLayout()
{
	if (inputLayoutDesc != nullptr)
		delete inputLayoutDesc;

	int elementCount = 0;

	std::string inputElements = "";
	
	std::string elementName = "";

	inputLayoutDesc = new D3D11_INPUT_ELEMENT_DESC[_inputLayoutElementList->size()];

	int debugref = -1;

	for (int i = 0; i < _inputLayoutElementList->size(); i++)
	{
		ShaderInputLayoutElement* element = _inputLayoutElementList->operator[](i);

		elementName = element->_semantic;

		std::transform(elementName.begin(), elementName.end(), elementName.begin(), ::tolower);

		inputLayoutDesc[elementCount].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

		if (elementCount == 0)
			inputLayoutDesc[elementCount].AlignedByteOffset = 0;
		
		D3D_REGISTER_COMPONENT_TYPE elementType = static_cast<D3D_REGISTER_COMPONENT_TYPE>(element->_type);

		inputLayoutDesc[elementCount].SemanticName = element->_semantic.c_str();
		inputLayoutDesc[elementCount].SemanticIndex = element->_index;

		inputLayoutDesc[elementCount].InputSlot = 0;
		inputLayoutDesc[elementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesc[elementCount].InstanceDataStepRate = 0;

		DXGI_FORMAT elementFormat;

		if (element->_mask == 1)
		{
			if (elementType == D3D_REGISTER_COMPONENT_UINT32) { elementFormat = DXGI_FORMAT_R32_UINT; _dataStride += sizeof(UINT); }
			else if (elementType == D3D_REGISTER_COMPONENT_SINT32) { elementFormat = DXGI_FORMAT_R32_SINT;  _dataStride += sizeof(INT); }
			else if (elementType == D3D_REGISTER_COMPONENT_FLOAT32) { elementFormat = DXGI_FORMAT_R32_FLOAT; _dataStride += sizeof(FLOAT); }
		}
		else if (element->_mask <= 3)
		{
			if (elementType == D3D_REGISTER_COMPONENT_UINT32) { elementFormat = DXGI_FORMAT_R32G32_UINT; _dataStride += sizeof(UINT[2]); }
			else if (elementType == D3D_REGISTER_COMPONENT_SINT32) { elementFormat = DXGI_FORMAT_R32G32_SINT; _dataStride += sizeof(INT[2]); }
			else if (elementType == D3D_REGISTER_COMPONENT_FLOAT32) { elementFormat = DXGI_FORMAT_R32G32_FLOAT; _dataStride += sizeof(FLOAT[2]); }
		}
		else if (element->_mask <= 7)
		{
			if (elementType == D3D_REGISTER_COMPONENT_UINT32) { elementFormat = DXGI_FORMAT_R32G32B32_UINT; _dataStride += sizeof(UINT[3]); }
			else if (elementType == D3D_REGISTER_COMPONENT_SINT32) { elementFormat = DXGI_FORMAT_R32G32B32_SINT; _dataStride += sizeof(INT[3]); }
			else if (elementType == D3D_REGISTER_COMPONENT_FLOAT32) { elementFormat = DXGI_FORMAT_R32G32B32_FLOAT; _dataStride += sizeof(FLOAT[3]); }
		}
		else if (element->_mask <= 15)
		{
			if (elementType == D3D_REGISTER_COMPONENT_UINT32) { elementFormat = DXGI_FORMAT_R32G32B32_UINT; _dataStride += sizeof(UINT[3]); }
			else if (elementType == D3D_REGISTER_COMPONENT_SINT32) { elementFormat = DXGI_FORMAT_R32G32B32_SINT; _dataStride += sizeof(INT[3]); }
			else if (elementType == D3D_REGISTER_COMPONENT_FLOAT32) { elementFormat = DXGI_FORMAT_R32G32B32_FLOAT; _dataStride += sizeof(FLOAT[3]); }
		}

		inputLayoutDesc[elementCount].Format = elementFormat;

		std::random_shuffle(elementName.begin(), elementName.end());

		inputElements += "float"; 
		inputElements = inputElements + ' ' + elementName + " : " + element->_semantic + "; ";

		switch (element->_class) {
			case INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA:
				inputLayoutDesc[elementCount].InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
				inputLayoutDesc[elementCount].InstanceDataStepRate = 1;
				inputLayoutDesc[elementCount].AlignedByteOffset = 0;
				break;
			case INPUT_LAYOUT_ELEMENT_CLASS::PER_VERTEX_DATA:
				inputLayoutDesc[elementCount].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
				inputLayoutDesc[elementCount].InstanceDataStepRate = 0;
				break;
		}

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

	HRESULT compileResult;
	HRESULT vCreateResult;
	HRESULT ILCreateResult;

	compileResult = D3DCompile(dumbyShaderStr.c_str(), dumbyShaderStr.size(),
		NULL, 0, 0, "Vshader", "vs_5_0", D3DCOMPILE_DEBUG, 0, &vertexShaderCode, &compileError);

	if (FAILED(compileResult)) {
		std::wstring errorMsg = L"INPUT LAYOUT FAKE SHADER COMPILE ERROR: ";
		errorMsg += L"Fake";
		errorMsg += L"\n";
		errorMsg += L"HLSL ERR: ";
		std::string compileErrStr((char*)compileError->GetBufferPointer());
		std::wstring tmp;
		tmp.assign(compileErrStr.begin(), compileErrStr.end());
		errorMsg += tmp;


		MessageBox(window::getInstance()->hWnd, errorMsg.c_str(), L"ERROR", MB_OK);

		OutputDebugStringA((char*)compileError->GetBufferPointer());
		compileError->Release();
	}

	vCreateResult = dxDeviceAccessor::dxEncapsulator->dxDev->
		CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);

	ILCreateResult = dxDeviceAccessor::dxEncapsulator->dxDev->
		CreateInputLayout(inputLayoutDesc, elementCount, vertexShaderCode->GetBufferPointer(),
			vertexShaderCode->GetBufferSize(), &_inputLayout);
}
