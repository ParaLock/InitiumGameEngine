#pragma once
#include "../../../sysInclude.h"

#include "../../Shaders/include/Shader.h"
#include "../../RenderingCore/include/ActiveAPITypeAccessor.h"

#include "../../Directx11Rendering/dxShaders/include/dxShader.h"

class ShaderFactory
{
public:
	ShaderFactory();
	~ShaderFactory();

	static Shader* createShader(LPCWSTR shaderFilename, LPCWSTR pipelineFilename);
};

