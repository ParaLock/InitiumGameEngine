#include "../include/Light.h"

Light::Light(IShader *shader)
{
	lightShader = shader;
}


Light::~Light()
{
}

void Light::updateVar(std::string varName, void * data)
{
	lightShader->updateVar(varName, data);
}

void Light::draw()
{
	lightShader->Bind();
}
