#include "../include/Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::loadImage(LPCWSTR filename)
{
	std::cout << "TEXTURE: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;
}

void Texture::updateParameter(std::string varName, void * data)
{
	std::cout << "TEXTURE: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;
}

void * Texture::getParameter(std::string varName)
{
	std::cout << "TEXTURE: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;;

	return nullptr;
}
