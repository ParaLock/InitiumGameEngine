#pragma once
#include "../../../sysInclude.h"
#include "../../Shaders/include/Shader.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

class Light
{
private:
	Shader* _shader = nullptr;
public:
	Light();
	~Light();

	void attachShader(Shader* newShader);

	void draw();
};

