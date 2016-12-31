#include "..\include\ShaderInputLayout.h"



ShaderInputLayout::ShaderInputLayout()
{
}


ShaderInputLayout::~ShaderInputLayout()
{
}

void ShaderInputLayout::addInput(std::string type, std::string name)
{
	_inputLayoutElementList->push_back(std::make_pair(type, name));
}

void ShaderInputLayout::updateParameter(std::string varName, void * data)
{
	std::cout << "SHADER INPUT LAYOUT: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;
}

void * ShaderInputLayout::getParameter(std::string varName)
{
	std::cout << "SHADER INPUT LAYOUT: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;
	return nullptr;
}

void ShaderInputLayout::generateInputLayout()
{
	std::cout << "SHADER INPUT LAYOUT: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;
}
