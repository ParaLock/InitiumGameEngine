#pragma once

#include "../../../sysInclude.h"
#include "../../Textures/include/Texture.h"
#include "../../../ResourceFramework/include/IResource.h"
#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../RenderNode/include/MeshRenderNode.h"
#include "../../RenderNodeTree/include/RenderNodeTree.h"
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

	void setShader(Shader* shader) { _shader = shader; }
	void setGPUPipeline(GPUPipeline* pipeline) { _pipeline = pipeline; }

	Vector4f getSpecularColor() { return _specularColor; }

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

	void createPass(std::string name, Shader* shader, GPUPipeline* pipeline);
	MaterialPass* getPass(std::string name);

	std::vector<uint64_t> generateClientRenderNodes(mesh* mesh, Texture* texture);
};

