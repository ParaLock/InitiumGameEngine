#pragma once
#include "../../../sysInclude.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

#include "ILight.h"

class LightBuilder : public IResourceBuilder {
public:
	LIGHT_TYPE _type;

	LightBuilder(LIGHT_TYPE type) {
		_type = type;
	}
};

class Light : public IResource, public ILight
{
private:

	LIGHT_TYPE _type;

	Matrix4f _viewMatrix, _projectionMatrix;
	
	bool _isShadowCaster = false;
	bool _lightViewMatDirty = false;

	struct GenericData {

		float _intensity = 0.0f;
		float _range = 0.0f;

		Vector3f _direction = Vector3f(0.0f, 0.0f, 0.0f);
		Vector3f _pos = Vector3f(0.0f, 0.0f, 0.0f);
		Vector4f _color = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);

	} _GenericData;

	struct Attenuation {
		float _constant = 0;
		float _linear = 0;
		float _exponent = 0;

	} _Attenuation;


public:
	Light();
	~Light();

	void load(IResourceBuilder* builder);
	void unload();

    void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	LIGHT_TYPE getType() { return _type; }

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

	Matrix4f getViewMatrix();
	Matrix4f getProjectionMatrix();

	bool getIsShadowCaster() { return _isShadowCaster; };
	void setIsShadowCaster(bool isShaderCaster) { _isShadowCaster = isShaderCaster; };
};

