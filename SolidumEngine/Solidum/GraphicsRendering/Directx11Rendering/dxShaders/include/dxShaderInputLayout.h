#pragma once
#include "../../../../sysInclude.h"
#include "../../../Shaders/include/ShaderInputLayout.h"
#include "../../dxDevice/include/dxDeviceAccessor.h"

class dxShaderInputLayout : public ShaderInputLayout
{
private:
	ID3D11InputLayout* _inputLayout;
public:
	dxShaderInputLayout(std::string name);
	~dxShaderInputLayout();

	void updateParameter(std::string varName, void *data);
	void* getParameter(std::string varName);

	void generateInputLayout();
};

