#pragma once

#include "../../../sysInclude.h"
#include "../../Textures/include/Texture.h"
#include "../../../ResourceFramework/include/Resource.h"
#include "../../../ResourceFramework/include/ResourceInitParams.h"

class Shader;

class GenericFactory;

class MaterialPass {
private:

	std::string _name;

	float _specularIntensity;
	float _specularPower;

	Shader* _shader;

	Vector4f _specularColor;

	Texture* _albedoTex = nullptr;
	Texture* _specularTex = nullptr;
	Texture* _normalTex = nullptr;
	Texture* _roughnessTex = nullptr;
	Texture* _emissiveTex = nullptr;

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

	Texture* getSpecularTexture() { return _specularTex; };
	Texture* getNormalTexture() { return _normalTex; };

	Texture* getPBRAlbedoTexture() { return _albedoTex; };
	Texture* getPBRRoughnessTexture() { return _roughnessTex; };
	Texture* getPBREmessiveTexture() { return _emissiveTex; };

	void setShader(Shader* shader) { _shader = shader; }

	Vector4f getSpecularColor() { return _specularColor; }

	Shader* getShader() { return _shader; }
};

class ResourcePool;

class Material : public Resource<Material, GenericFactory, ResourcePool>
{
private:
	std::map<std::string, MaterialPass*> _passes;
public:
	Material();
	~Material();

	void load();
	void unload();

	struct InitData : public ResourceInitParams {

		InitData() {

		}

		
	};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void createPass(std::string name, Shader* shader);

	MaterialPass* getPass(std::string name);

	std::vector<MaterialPass*> getPassList();
protected:
};

