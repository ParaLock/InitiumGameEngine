#include "../include/Material.h"

Material::Material(float specPower, float specIntensity, Vector4f specColor, int ID)
{
	this->_specularIntensity = specIntensity;
	this->_specularPower = specPower;
	this->_specularColor = specColor;
	this->_ID = ID;
}

Material::~Material()
{
}

void Material::attachMaterialTexture(Texture * tex, MATERIAL_TEX texType)
{
	auto itr = _textures.find(texType);

	if (itr == _textures.end()) {
		_textures.insert({texType, tex});
	}
}

