#include "../include/Material.h"

Material::Material(float shine, float specPower, Vector4f specColor)
{
	this->_specularShininess = shine;
	this->_specularPower = specPower;
	this->_specularColor = specColor;
}

Material::~Material()
{
}
