#pragma once

#include "../../../sysInclude.h"
#include "../../Textures/include/Texture.h"
#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Shaders/include/Shader.h"
#include "../../GraphicsCore/include/GraphicsCore.h"


class MaterialBuilder : public IResourceBuilder {
public:

	MaterialBuilder() {
	}
};

class MaterialPass {
private:

	std::string _name;

	float _specularIntensity;
	float _specularPower;

	Shader* _shader;
	GPUPipeline* _pipeline;

	Vector4f _specularColor;

	std::map<MATERIAL_TEX, Texture*> _textures;

public:
	MaterialPass() {}

	void setName(std::string name) { _name = name; }

	void setSpecularIntensity(float intensity) { _specularIntensity = intensity; }
	void setSpecularPower(float power) { _specularPower = power; }
	void setSpecularColor(Vector4f specColor) { _specularColor = specColor; }

	float getSpecularIntensity() { return _specularIntensity; }
	float getSpecularPower() { return _specularPower; }

	void setSpecularTexture(Texture* tex);
	void setNormalTexture(Texture* tex);

	void setPBRAlbedoTexture(Texture* tex);
	void setPBRRoughnessTexture(Texture* tex);
	void setPBREmessiveTexture(Texture* tex);

	void setShader(Shader* shader) { _shader = shader; }
	void setGPUPipeline(GPUPipeline* pipeline) { _pipeline = pipeline; }

	Vector4f getSpecularColor() { return _specularColor; }

	const std::map<MATERIAL_TEX, Texture*>& getTextures() { return _textures; }

	Shader* getShader() { return _shader; }
	GPUPipeline* getPipeline() { return _pipeline; }
};


class Material : public IResource
{
private:
	std::map<std::string, MaterialPass*> _passes;
public:
	Material();
	~Material();

	void load(IResourceBuilder* builder);
	void unload();

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void createPass(std::string name, Shader* shader, GPUPipeline* pipeline);

	MaterialPass* getPass(std::string name);

	std::vector<MaterialPass*> getPassList();
};

