#pragma once
#include "../../../../sysInclude.h"
#include "../../../Shaders/include/ShaderInputLayout.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class IResourceBuilder;

class dxShaderInputLayout : public ShaderInputLayout
{
private:
	ID3D11InputLayout* _inputLayout;
public:
	dxShaderInputLayout();
	~dxShaderInputLayout();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void addInput(int type, std::string name, UINT index, BYTE mask);

	void generateInputLayout();
};

