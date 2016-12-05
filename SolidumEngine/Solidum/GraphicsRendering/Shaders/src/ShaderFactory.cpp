#include "../include/ShaderFactory.h"



ShaderFactory::ShaderFactory()
{
}


ShaderFactory::~ShaderFactory()
{
}

std::map<std::string, IShader*>* ShaderFactory::shaderLibrary = new std::map<std::string, IShader*>;

IShader* ShaderFactory::createShader(LPCWSTR filename, int shaderType, std::string ID)
{
	IShader* newShader;

	switch (shaderType) {
	case DXSHADER_TYPE_DirectionalLight:
		newShader = new dxShader(filename, "post_process_stage");
		break;
	case DXSHADER_TYPE_DEFERRED:
		newShader = new dxShader(filename, "geometry_stage");
		break;
	case DXSHADER_TYPE_SpotLight:
		newShader = new dxShader(filename, "post_process_stage");
		break;
	default:
		newShader = NULL;
		break;
	}

	shaderLibrary->insert({ID, newShader});

	return newShader;
}

IShader * ShaderFactory::requestShader(std::string ID)
{
	return shaderLibrary->at(ID);
}

void ShaderFactory::destroyShaderLibrary()
{
	for (std::map<std::string, IShader*>::iterator itr = shaderLibrary->begin(); itr != shaderLibrary->end(); itr++) {
		IShader *shaderToRemove = itr->second;
		delete shaderToRemove;
	}

	shaderLibrary->clear();
	delete shaderLibrary;
}
