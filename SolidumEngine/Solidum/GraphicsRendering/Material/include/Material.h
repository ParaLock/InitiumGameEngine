#pragma once

#include "../../../sysInclude.h"

#include "../../Textures/include/Texture.h"

typedef enum MATERIAL_TEX {
	PRIMARY_MATERIAL_TEXTURE,
	SECONDARY_MATERIAL_TEXTURE
};

class Material
{
private:

	int _ID;

	float _specularIntensity;
	float _specularPower;
	Vector4f _specularColor;

	std::map<MATERIAL_TEX, Texture*> _textures;

public:
	Material(float specIntensity, float specPower, Vector4f specColor, int ID);
	~Material();

	void attachMaterialTexture(Texture* tex, MATERIAL_TEX texType);

	void setSpecularIntensity(float intensity) { _specularIntensity = intensity; }
	void setSpecularPower(float power) { _specularPower = power; }
	void setSpecularColor(Vector4f specColor) { _specularColor = specColor; }

	float getSpecularIntensity() { return _specularIntensity; }
	float getSpecularPower() { return _specularPower; }

	Vector4f getSpecularColor() { return _specularColor; }

	int getID() { return _ID; }

	std::map<MATERIAL_TEX, Texture*>& const getTextures() { return _textures; };
};

