#include "../include/Light.h"

Light::Light()
{
	_projectionMatrix = Matrix4f::get_identity();
	_viewMatrix = Matrix4f::get_identity();
	_shadowMatrix = Matrix4f::get_identity();

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

void Light::shadowUpdate(BoundingSphere * worldSphere)
{

	if (_type == LIGHT_TYPE::DIRECTIONAL_LIGHT) {

		auto sceneBoundsRadius = worldSphere->getRadius();
		auto sceneBoundsCenter = worldSphere->getCenter();

		auto lightDir = _GenericData._direction;

		auto midMult = lightDir * -2.0f;

		auto lightPos = midMult * sceneBoundsRadius;
		auto targetPos = sceneBoundsCenter;
		auto up = Vector3f(0, 1, 0);

		auto v = Matrix4f::get_lookAtLH(lightPos, targetPos, up);

		auto sphereCenterLS = Matrix4f::transform(targetPos, v);

		auto l = sphereCenterLS[0] - sceneBoundsRadius;
		auto b = sphereCenterLS[1] - sceneBoundsRadius;
		auto n = sphereCenterLS[2] - sceneBoundsRadius;
		auto r = sphereCenterLS[0] + sceneBoundsRadius;
		auto t = sphereCenterLS[1] + sceneBoundsRadius;
		auto f = sphereCenterLS[2] + sceneBoundsRadius;

		auto p = Matrix4f::get_orthographicOffCenterLH(l, r, b, t, n, f);

		//p = Matrix4f::get_perspective(((float)M_PI / 2.0f), 1.0f, 1.0f, 100.0f);


		auto s = v * p;

		_viewMatrix = v;
		_projectionMatrix = p;


		_shadowMatrix = s;
	}
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
