#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::setMesh(mesh* newMesh)
{
	_pipelineState->setHookResource(newMesh->getIndexBuff(), "index_buffer");
	_pipelineState->setHookResource(newMesh->getVertexBuff(), "vertex_buffer");
}

void Shader::setModelTexture(Texture * tex)
{
	_pipelineState->setHookResource(tex, "model_tex");
}

void Shader::updateMaterialUniforms(Material* mat)
{
	float specPower = mat->getSpecularPower();
	float specIntensity= mat->getSpecularIntensity();
	int matID = mat->getID();

	updateUniform("cbuff_specularIntensity", &specIntensity);
	updateUniform("cbuff_specularColor", &mat->getSpecularColor());
	updateUniform("cbuff_specularPower", &specPower);
	updateUniform("cbuff_materialID", &specPower);

	std::map<MATERIAL_TEX, Texture*>& const textures = mat->getTextures();

	for (auto itr = textures.begin(); itr != textures.end(); itr++) {
		if (itr->first == MATERIAL_TEX::PRIMARY_MATERIAL_TEXTURE) {
			_pipelineState->setHookResource(itr->second, "material_color_tex");
		}
		if (itr->first == MATERIAL_TEX::SECONDARY_MATERIAL_TEXTURE) {
			_pipelineState->setHookResource(itr->second, "material_base_tex");
		}
	}
}

void Shader::updateLightUniforms(ILight* light)
{
	float intensity = light->getIntensity();
	float constant = light->getAttenuationConstant();
	float linear = light->getAttenuationLinear();
	float exponent = light->getAttenuationExponent();
	float range = light->getRange();

	updateUniform("cbuff_lightDirection", &light->getDirection());
	updateUniform("cbuff_lightPos", &light->getPosition());
	updateUniform("cbuff_lightColor", &light->getColor());
	updateUniform("cbuff_lightIntensity", &intensity);
	updateUniform("cbuff_pointLightRange", &range);
	updateUniform("cbuff_pointLightConstant", &constant);
	updateUniform("cbuff_pointLightLinear", &linear);
	updateUniform("cbuff_pointLightExponent", &exponent);
}

void Shader::updateModelUniforms(Transform* transform)
{
	updateUniform("cbuff_OBJSpecificMatrix", transform->getTransposedTransform());
}

void Shader::updateCameraUniforms(camera* cam)
{
	updateUniform("cbuff_eyePos", cam->getView());
	updateUniform("cbuff_viewMatrix", cam->getTransposedViewMatrix());
	updateUniform("cbuff_projectionMatrix", cam->getTransposedProjectionMatrix());
	updateUniform("cbuff_worldMatrix", cam->getTransposedWorldMatrix());
	updateUniform("cbuff_orthoProjection", cam->getOrtho());
	updateUniform("cbuff_camViewStart", cam->getTransposedStartCamView());
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

void Shader::attachPipeline(GPUPipeline* pipe)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}
