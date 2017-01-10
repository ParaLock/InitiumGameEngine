#include "../include/Light.h"

Light::Light(int type)
{
	_type = type;
}


Light::~Light()
{
}

void Light::setDirection(Vector3f dir) {

	_direction = dir;
}

void Light::setPosition(Vector3f pos) {

	_pos = pos;
}

void Light::setColor(Vector4f color) {

	_color = color;
}

void Light::attachShader(Shader * newShader)
{
	_shader = newShader;
}
