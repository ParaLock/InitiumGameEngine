#include "../include/Light.h"

Light::Light()
{
	_projectionMatrix = Matrix4f::get_identity();
	_viewMatrix = Matrix4f::get_identity();

	_projectionMatrix = Matrix4f::get_orthographic(-10, 10, -10, 10, 1.0f, 100.0f);

	//_projectionMatrix = Matrix4f::get_perspective(((float)M_PI / 2.0f), 1.0f, 1.0f, 100.0f);

	_isShadowCaster = true;
}


Light::~Light()
{
}

void Light::load(std::shared_ptr<IResourceBuilder> builder)
{
	InitData* realBuilder = static_cast<InitData*>(builder.get());

	_type = realBuilder->_type;

	isLoaded = true;
}

void Light::unload()
{
	isLoaded = false;
}

void Light::setDirection(Vector3f dir) {

	_lightViewMatDirty = true;

	_GenericData._direction = dir;
}

void Light::setPosition(Vector3f pos) {

	_lightViewMatDirty = true;

	_GenericData._pos = pos;
}

void Light::setColor(Vector4f color) {

	_GenericData._color = color;
}

void Light::setIntensity(float intensity)
{
	_GenericData._intensity = intensity;
}

void Light::setAttenuationConstant(float constant)
{
	_Attenuation._constant = constant;
}

void Light::setAttenuationLinear(float linear)
{
	_Attenuation._linear = linear;
}

void Light::setAttenuationExponent(float exponent)
{
	_Attenuation._exponent = exponent;
}

Matrix4f Light::getViewMatrix()
{
	if (_lightViewMatDirty) {

		_viewMatrix = Matrix4f::get_lookAt(_GenericData._direction, Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));

		_lightViewMatDirty = false;
	}

	return _viewMatrix;
}

Matrix4f Light::getProjectionMatrix()
{
	return _projectionMatrix;
}

Matrix4f Light::getModelMatrix()
{
	return Matrix4f::get_translation(_GenericData._pos);
}

void Light::updateDirLightProjectionAndView()
{

}
