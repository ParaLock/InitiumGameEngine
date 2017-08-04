#include "../include/Material.h"

Material::Material()
{
}

Material::~Material()
{
}

void Material::load()
{
}

void Material::unload()
{
}

void Material::createPass(std::string name, Shader * shader)
{
	MaterialPass* newPass = new MaterialPass;

	newPass->setShader(shader);

	_passes.insert({name, newPass });
}

MaterialPass * Material::getPass(std::string name)
{
	return _passes[name];
}

std::vector<MaterialPass*> Material::getPassList()
{
	std::vector<MaterialPass*> passes;
	
	for (auto itr = _passes.begin(); itr != _passes.end(); itr++) {
		passes.push_back(itr->second);
	}

	return passes;
}

void MaterialPass::setSpecularTexture(Texture * tex)
{
	_specularTex = tex;
}

void MaterialPass::setNormalTexture(Texture * tex)
{
	_normalTex = tex;
}

void MaterialPass::setPBRAlbedoTexture(Texture * tex)
{
	_albedoTex = tex;
}

void MaterialPass::setPBRRoughnessTexture(Texture * tex)
{
	_roughnessTex = tex;
}

void MaterialPass::setPBREmessiveTexture(Texture * tex)
{
	_emissiveTex = tex;
}
