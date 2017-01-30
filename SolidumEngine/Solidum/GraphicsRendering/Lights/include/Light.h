#pragma once
#include "../../../sysInclude.h"
#include "../../Camera/include/camera.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "../../Shaders/include/Shader.h"

#include "ILight.h"

class LightBuilder : public IResourceBuilder {
public:
	LightBuilder() {

	}
};

class Light : public IResource, public ILight
{
private:
	Shader* _shader = nullptr;

	struct GenericData {

		float _intensity;
		float _range;

		Vector3f _direction;
		Vector3f _pos;
		Vector4f _color;

	} _GenericData;

	struct Attenuation {
		float _constant;
		float _linear;
		float _exponent;

	} _Attenuation;


public:
	Light(IResourceBuilder* builder);
	~Light();

	void setDirection(Vector3f dir);
	void setPosition(Vector3f pos);
	void setColor(Vector4f color);

	void setIntensity(float intensity);
	void setRange(float range) { _GenericData._range = range; };
	
	void setAttenuationConstant(float constant);
	void setAttenuationLinear(float linear);
	void setAttenuationExponent(float exponent);

	Vector3f getDirection() { return _GenericData._direction; }
	Vector3f getPosition() { return _GenericData._pos; }
	Vector4f getColor() { return _GenericData._color; }

	float getIntensity() { return _GenericData._intensity; };
	float getRange() { return _GenericData._range; }

	float getAttenuationConstant() { return _Attenuation._constant; }
	float getAttenuationLinear() { return _Attenuation._linear; }
	float getAttenuationExponent() { return _Attenuation._exponent; }

	Shader* getShader() { return _shader; }

	void attachShader(Shader* newShader);

};

