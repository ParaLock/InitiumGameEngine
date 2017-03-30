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

	isLoaded = true;
}

void Material::unload()
{
	isLoaded = false;
}

void Material::createPass(std::string name, Shader * shader, GPUPipeline * pipeline)
{
	MaterialPass* newPass = new MaterialPass;

	shader->attachPipeline(pipeline);
	
	newPass->setShader(shader);
	newPass->setGPUPipeline(pipeline);

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
	_textures.insert({ MATERIAL_TEX::SPECULAR_MAT_TEXTURE, tex});
}

void MaterialPass::setNormalTexture(Texture * tex)
{
	_textures.insert({ MATERIAL_TEX::NORMAL_MAT_TEXTURE, tex });
}

void MaterialPass::setPBRAlbedoTexture(Texture * tex)
{
	_textures.insert({ MATERIAL_TEX::ALBEDO_MAT_TEXTURE, tex });
}

void MaterialPass::setPBRRoughnessTexture(Texture * tex)
{
	_textures.insert({ MATERIAL_TEX::ROUGHNESS_PBR_TEXTURE, tex });
}

void MaterialPass::setPBREmessiveTexture(Texture * tex)
{
	_textures.insert({ MATERIAL_TEX::EMESSIVE_PBR_TEXTURE, tex });
}
