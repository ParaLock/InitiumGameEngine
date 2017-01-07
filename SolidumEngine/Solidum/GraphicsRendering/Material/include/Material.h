#pragma once

#include "../../../sysInclude.h"

class Material
{
private:

	float _specularShininess;
	float _specularPower;
	Vector4f _specularColor;

public:
	Material(float shine, float specPower, Vector4f specColor);
	~Material();

	void setShininess(float shine) { _specularShininess = shine; }
	void setSpecularPower(float power) { _specularPower = power; }
	void setSpecularColor(Vector4f specColor) { _specularColor = specColor; }

	float getSpecularShininess() { return _specularShininess; }
	float getSpecularPower() { return _specularPower; }

	Vector4f getSpecularColor() { return _specularColor; }
};

