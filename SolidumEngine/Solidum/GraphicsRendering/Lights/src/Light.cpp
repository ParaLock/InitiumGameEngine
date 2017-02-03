#include "../include/Light.h"

Light::Light()
{
}


Light::~Light()
{
}

void Light::load(IResourceBuilder * builder)
{
	isLoaded = true;
}

void Light::unload()
{
	isLoaded = false;
}

void Light::setDirection(Vector3f dir) {

	_GenericData._direction = dir;
}

void Light::setPosition(Vector3f pos) {

	_GenericData._pos = pos;
}

void Light::setColor(Vector4f color) {

	_GenericData._color = color;
}

void Light::setIntensity(float intensity)
{
	_GenericData._intensity = intensity;
}

void Light::setAttenuationConstant(float constant)
{
	_Attenuation._constant = constant;
}

void Light::setAttenuationLinear(float linear)
{
	_Attenuation._linear = linear;
}

void Light::setAttenuationExponent(float exponent)
{
	_Attenuation._exponent = exponent;
}

void Light::attachShader(Shader * newShader)
{
	_shader = newShader;
}
