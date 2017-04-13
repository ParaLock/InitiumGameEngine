#pragma once
#include "../../../sysInclude.h"

struct Viewport
{
private:

public:
	Viewport(int height, int width, float maxDepth, float minDepth);
	Viewport(Viewport& viewport);
	Viewport();
	~Viewport();

	int _height = 0, _width = 0;
	float _minDepth = 0.0f, _maxDepth = 0.0f;
};

