#include "../include/Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::load(IResourceBuilder * builder)
{
	MaterialBuilder* realBuilder = static_cast<MaterialBuilder*>(builder);

	this->_specularIntensity = realBuilder->_specIntensity;
	this->_specularPower = realBuilder->_specPower;
	this->_specularColor = realBuilder->_specColor;
	this->_ID = realBuilder->_ID;

	isLoaded = true;
}

void Material::unload()
{
	isLoaded = false;
}

void Material::attachMaterialTexture(Texture* tex, MATERIAL_TEX texType)
{
	auto itr = _textures.find(texType);

	if (itr == _textures.end()) {
		_textures.insert({texType, tex});
	}
}

