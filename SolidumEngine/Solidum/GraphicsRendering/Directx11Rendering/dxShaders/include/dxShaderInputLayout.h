#pragma once
#include "../../../../sysInclude.h"
#include "../../../Shaders/include/ShaderInputLayout.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class ResourceInitParams;

class dxShaderInputLayout : public ShaderInputLayout
{
private:
	ID3D11InputLayout* _inputLayout = nullptr;
	D3D11_INPUT_ELEMENT_DESC *inputLayoutDesc = nullptr;
	int _numInstanceElements = 0;
public:
	dxShaderInputLayout();
	~dxShaderInputLayout();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void addInput(int type, std::string name, UINT index, BYTE mask);

	void generateInputLayout();
};

