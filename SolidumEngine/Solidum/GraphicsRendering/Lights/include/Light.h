#pragma once
#include "../../../sysInclude.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

class Shader;

class Light
{
private:
	Shader* _shader = nullptr;

	Vector3f _direction;
	Vector3f _pos;

	Vector4f _color;

	int _type;

public:
	Light(int type);
	~Light();

	void setDirection(Vector3f dir);
	void setPosition(Vector3f pos);
	void setColor(Vector4f color);

	void setType(int type) { _type = type; };

	Vector3f getDirection() { return _direction; }
	Vector3f getPosition() { return _pos; }
	Vector4f getColor() { return _color; }

	int getType() { return _type; };

	Shader* getShader() { return _shader; }

	void attachShader(Shader* newShader);

};

