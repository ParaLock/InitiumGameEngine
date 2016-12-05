#pragma once
#include "../../../sysInclude.h"

#include "../../Shaders/include/ShaderFactory.h"
#include "../../GraphicsBuffers/include/GraphicsBufferFactory.h"

class Light
{
private:

	IShader *lightShader;

public:
	Light(IShader *shader);
	~Light();

	void updateVar(std::string varName, void *data);

	void draw();
};

