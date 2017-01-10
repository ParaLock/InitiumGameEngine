#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::setMesh(mesh * newMesh)
{
	_pipelineState->setBuffer(newMesh->getIndexBuff(), "index_buffer");
	_pipelineState->setBuffer(newMesh->getVertexBuff(), "vertex_buffer");
}

void Shader::updateMaterialUniforms(Material * mat)
{
	float specPower = mat->getSpecularPower();
	float specIntensity= mat->getSpecularIntensity();
	int matID = mat->getID();

	updateUniform("specularIntensity", &specIntensity);
	updateUniform("specularColor", &mat->getSpecularColor());
	updateUniform("specularPower", &specPower);
	updateUniform("materialID", &specPower);

	std::map<MATERIAL_TEX, Texture*>& const textures = mat->getTextures();

	for (auto itr = textures.begin(); itr != textures.end(); itr++) {
		if (itr->first == MATERIAL_TEX::PRIMARY_MATERIAL_TEXTURE) {
			_pipelineState->setTexture(itr->second, "material_color_tex");
		}
		if (itr->first == MATERIAL_TEX::SECONDARY_MATERIAL_TEXTURE) {
			_pipelineState->setTexture(itr->second, "material_base_tex");
		}
	}
}

void Shader::updateLightUniforms(Light * light)
{
	int lightType = light->getType();

	updateUniform("lightDirection", &light->getDirection());
	updateUniform("lightPos", &light->getPosition());
	updateUniform("lightColor", &light->getColor());
	updateUniform("lightType", &lightType);
}

void Shader::updateModelUniforms(Transform * transform)
{
	updateUniform("OBJSpecificMatrix", transform->getTransform());
}

void Shader::updateCameraUniforms(camera * cam)
{
	updateUniform("eyePos", cam->getView());
	updateUniform("viewMatrix", cam->getTransposedViewMatrix());
	updateUniform("projectionMatrix", cam->getTransposedProjectionMatrix());
	updateUniform("worldMatrix", cam->getTransposedWorldMatrix());
	updateUniform("orthoProjection", cam->getOrtho());
	updateUniform("camViewStart", cam->getTransposedStartCamView());
}

void Shader::execute(int numIndices)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void Shader::updateUniform(std::string varName, void * pData)
{
	auto itr = _uniformVarNameToBuff->find(varName);

	if (itr != _uniformVarNameToBuff->end()) {

		DynamicBuffer* varsBuff = _uniformVarNameToBuff->at(varName);

		varsBuff->updateVar(varName, pData);
	}
}

void Shader::updateGPU()
{
	DynamicBuffer* previous = nullptr;

	std::vector<DynamicBuffer*> activeGeneralDataBuffers;

	for (auto itr = _uniformVarNameToBuff->begin(); itr != _uniformVarNameToBuff->end(); itr++) {

		if (itr->second != previous)
			activeGeneralDataBuffers.push_back(itr->second);

		previous = itr->second;
	}

	for (unsigned int i = 0; i < activeGeneralDataBuffers.size(); ++i) {
		activeGeneralDataBuffers[i]->updateGPU();
	}
}
