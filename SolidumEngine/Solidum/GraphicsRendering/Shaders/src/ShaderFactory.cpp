#include "../include/ShaderFactory.h"



ShaderFactory::ShaderFactory()
{
}


ShaderFactory::~ShaderFactory()
{
}

Shader * ShaderFactory::createShader(LPCWSTR shaderFilename, LPCWSTR pipelineFilename)
{
	Shader* newShader;

	switch (ActiveAPITypeAccessor::_apiInUse) {
	case DIRECTX11:
		newShader = new dxShader(shaderFilename, pipelineFilename);
		break;
	}

	return newShader;
}
