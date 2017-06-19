#include "../include/Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

void Shader::updateMaterialPassUniforms(MaterialPass* pass, RenderFlowGraphIOInterface* ioInterface)
{
	//NOT IMPLEMENTED
}

void Shader::updateDeferredLightUniforms(ILight* light)
{
	float intensity = light->getIntensity();
	float constant = light->getAttenuationConstant();
	float linear = light->getAttenuationLinear();
	float exponent = light->getAttenuationExponent();
	float range = light->getRange();

	Vector3f pos = light->getPosition();

	updateUniform("cbuff_lightDirection", &light->getDirection());
	updateUniform("cbuff_lightPos", &pos);
	updateUniform("cbuff_lightColor", &light->getColor());
	updateUniform("cbuff_lightIntensity", &intensity);
	updateUniform("cbuff_pointLightRange", &range);
	updateUniform("cbuff_pointLightConstant", &constant);
	updateUniform("cbuff_pointLightLinear", &linear);
	updateUniform("cbuff_pointLightExponent", &exponent);
}

void Shader::updatePointLightsForwardRendering(std::vector<ILight*> pointLights)
{
	struct PointLight {
		Vector3f lightPos;
		float range;
		Vector3f lightDirection;
		float intensity;
		Vector4f lightColor;

		float AttenConstant;
		float AttenLinear;
		float AttenExponent;
		float padding3;
	};

	PointLight lights[MAX_FORWARD_RENDERING_LIGHTS];

	for (int i = 0; i < MAX_FORWARD_RENDERING_LIGHTS; i++) {

		if (i < pointLights.size()) {

			lights[i].AttenConstant = pointLights[i]->getAttenuationConstant();
			lights[i].AttenLinear = pointLights[i]->getAttenuationLinear();
			lights[i].AttenExponent = pointLights[i]->getAttenuationExponent();

			lights[i].range = pointLights[i]->getRange();

			lights[i].intensity = pointLights[i]->getIntensity();
			lights[i].lightPos = pointLights[i]->getPosition();
			lights[i].lightDirection = pointLights[i]->getDirection();
			lights[i].lightColor = pointLights[i]->getColor();
		}
		else {
			lights[i].AttenConstant = 0.0f;
			lights[i].AttenLinear = 0.0f;
			lights[i].AttenExponent = 0.0f;
			lights[i].range = 0.0f;

			lights[i].intensity = 0.0f;
			lights[i].lightPos = Vector3f(0.0f, 0.0f, 0.0f);
			lights[i].lightDirection = Vector3f(0.0f, 0.0f, 0.0f);
			lights[i].lightColor = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		}

	}

	updateUniform("pointLights", &lights);
}

void Shader::updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights)
{
	struct DirectionalLight
	{
		Vector3f lightPos;
		float intensity;
		Vector3f lightDirection;
		float padding;
		Vector4f lightColor;
	};

	DirectionalLight lights[MAX_FORWARD_RENDERING_LIGHTS];

	for (int i = 0; i < MAX_FORWARD_RENDERING_LIGHTS; i++) {

		if (i < dirLights.size()) {

			lights[i].intensity = dirLights[i]->getIntensity();
			lights[i].lightPos = dirLights[i]->getPosition();
			lights[i].lightDirection = dirLights[i]->getDirection();
			lights[i].lightColor = dirLights[i]->getColor();
		}
		else {

			lights[i].intensity = 0.0f;
			lights[i].lightPos = Vector3f(0.0f, 0.0f, 0.0f);
			lights[i].lightDirection = Vector3f(0.0f, 0.0f, 0.0f);
			lights[i].lightColor = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
	updateUniform("directionalLights", &lights);
}


void Shader::updateModelUniforms(Transform* transform)
{
	updateUniform("cbuff_OBJSpecificMatrix", &Matrix4f::transpose(transform->getGlobalTransform()));
}

void Shader::updateCameraUniforms(CameraComponent* cam)
{
	updateUniform("cbuff_eyePos", &cam->getPos());
	updateUniform("cbuff_viewMatrix", &Matrix4f::transpose(cam->getViewMatrix()));
	updateUniform("cbuff_projectionMatrix", &Matrix4f::transpose(cam->getProjectionMatrix()));
	updateUniform("cbuff_worldMatrix", &Matrix4f::transpose(cam->getWorldMatrix()));
	updateUniform("cbuff_orthoProjection", &Matrix4f::transpose(cam->getOrthoProjectionMatrix()));
	updateUniform("cbuff_camViewStart", &Matrix4f::transpose(cam->getStartViewMatrix()));
}

void Shader::execute(GraphicsCommandList* commandList)
{
	std::cout << "GENERIC SHADER: NO GRAPHICS API DIRECTIVE DETECTED" << std::endl;
}

void Shader::updateUniform(std::string varName, void * pData)
{
	auto itr = _varNameToConstantBuffer.find(varName);

	if (itr != _varNameToConstantBuffer.end()) {

		DynamicStruct* varsBuff = _varNameToConstantBuffer.at(varName).second;

		varsBuff->updateVar(varName, pData);
	}
}

void Shader::updateGPU()
{
	for (auto itr = _varNameToConstantBuffer.begin(); itr != _varNameToConstantBuffer.end(); itr++) {
		DynamicStruct* buff = itr->second.second;
		buff->updateGPU();
	}
}
