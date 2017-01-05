#include "../include/Light.h"

Light::Light()
{
}


Light::~Light()
{
}


void Light::attachShader(Shader * newShader)
{
	_shader = newShader;
}

void Light::draw()
{
	if (_shader != nullptr) {
		_shader->updateGPU();

		_shader->execute(6);
	}
}
