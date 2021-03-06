#pragma once
#include "../../../sysInclude.h"

class Shader;
class BoundingSphere;

class ILight
{
public:
	ILight();
	~ILight();

	virtual LIGHT_TYPE getType() = 0;

	virtual Vector3f getDirection() = 0;
	virtual Vector3f getPosition() = 0;
	virtual Vector4f getColor() = 0;

	virtual void setPosition(Vector3f pos) = 0;

	virtual float getIntensity() = 0;
	virtual float getRange() = 0;

	virtual float getAttenuationConstant() = 0;
	virtual float getAttenuationLinear() = 0;
	virtual float getAttenuationExponent() = 0;

	virtual Matrix4f getViewMatrix() = 0;
	virtual Matrix4f getProjectionMatrix() = 0;
	virtual Matrix4f getModelMatrix() = 0;
	virtual Matrix4f getShadowMatrix() = 0;

	virtual void shadowUpdate(BoundingSphere* worldSphere) = 0;

	virtual void setDirection(Vector3f dir) = 0;
	virtual void setColor(Vector4f color) = 0;
	virtual void setIntensity(float intensity) = 0;

	virtual bool getIsShadowCaster() = 0;
	virtual void setIsShadowCaster(bool isShaderCaster) = 0;
};

