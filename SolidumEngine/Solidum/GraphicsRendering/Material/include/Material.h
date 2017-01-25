#pragma once

#include "../../../sysInclude.h"
#include "../../Textures/include/Texture.h"
#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"

class MaterialBuilder : public IResourceBuilder {
public:
	int _ID;

	float _specIntensity;
	float _specPower; 

	Vector4f _specColor; 

	MaterialBuilder(int ID, float specIntensity, float specPower, Vector4f specColor) {
		_ID = ID;
		_specIntensity = specIntensity;
		_specPower = specPower;
		_specColor = specColor;
	}
};

enum MATERIAL_TEX {
	PRIMARY_MATERIAL_TEXTURE,
	SECONDARY_MATERIAL_TEXTURE
};

class Material : public IResource
{
private:
	int _ID;

	float _specularIntensity;
	float _specularPower;

	Vector4f _specularColor;

	std::map<MATERIAL_TEX, Texture*> _textures;

public:
	Material(IResourceBuilder* builder);
	~Material();

	void attachMaterialTexture(Texture* tex, MATERIAL_TEX texType);

	void setSpecularIntensity(float intensity) { _specularIntensity = intensity; }
	void setSpecularPower(float power) { _specularPower = power; }
	void setSpecularColor(Vector4f specColor) { _specularColor = specColor; }

	float getSpecularIntensity() { return _specularIntensity; }
	float getSpecularPower() { return _specularPower; }

	Vector4f getSpecularColor() { return _specularColor; }

	int getID() { return _ID; }

	std::map<MATERIAL_TEX, Texture*>& getTextures() { return _textures; };
};

