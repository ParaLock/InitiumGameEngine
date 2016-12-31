#include "../include/RenderTarget.h"



RenderTarget::RenderTarget()
{
	
}


RenderTarget::~RenderTarget()
{
}

void RenderTarget::updateParameter(std::string varName, void * data)
{
	std::cout << "RENDER TARGET: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void * RenderTarget::getParameter(std::string varName)
{
	std::cout << "RENDER TARGET: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;

	return nullptr;
}


void RenderTarget::Clear(float R, float G, float B, float A)
{
	std::cout << "RENDER TARGET: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

