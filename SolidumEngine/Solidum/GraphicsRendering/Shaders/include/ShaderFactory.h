#pragma once

#include "../../../sysInclude.h"

#include "../../Directx11Rendering/dxShaders/include/dxShader.h"

class ShaderFactory
{
private:
	static std::map<std::string, IShader*> *shaderLibrary;
public:
	ShaderFactory();
	~ShaderFactory();

	static IShader* createShader(LPCWSTR filename, int shaderType, std::string ID);

	static IShader* requestShader(std::string ID);

	static void destroyShaderLibrary();

};

