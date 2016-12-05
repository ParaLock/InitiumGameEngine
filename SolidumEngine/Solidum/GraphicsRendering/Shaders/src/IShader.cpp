#include "../include/IShader.h"



IShader::IShader()
{
}


IShader::~IShader()
{
}

void IShader::attachTex(ITexture *tex)
{
	std::cout << "Shader Does not Support Texture Binding" << std::endl;
}
