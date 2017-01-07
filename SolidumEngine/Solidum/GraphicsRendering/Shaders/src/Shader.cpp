#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::setTexture(Texture * tex)
{
	_pipelineState->setPrimaryTexture(tex);
}

void Shader::setMesh(mesh * newMesh)
{
	_pipelineState->setIndexBuffer(newMesh->getIndexBuff());
	_pipelineState->setVertexBuffer(newMesh->getVertexBuff());
}

void Shader::updateMaterialUniforms(Material * mat)
{
	float specColor = mat->getSpecularPower();
	float specShininess = mat->getSpecularShininess();

	updateUniform("specularShininess", &specShininess);
	updateUniform("specularColor", &mat->getSpecularColor());
	updateUniform("specularPower", &specColor);
}

void Shader::updateLightUniforms(Light * light)
{
	updateUniform("lightDirection", &light->getDirection());
	updateUniform("lightPos", &light->getPosition());
	updateUniform("lightColor", &light->getColor());
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
