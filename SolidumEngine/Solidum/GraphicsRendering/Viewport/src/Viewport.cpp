#include "../include/Viewport.h"



Viewport::Viewport(int height, int width, float maxDepth, float minDepth)
{
	_height = height;
	_width = width;
	_maxDepth = maxDepth;
	_minDepth = minDepth;
}

Viewport::Viewport(Viewport & viewport)
{
	_height = viewport._height;
	_width = viewport._width;
	_maxDepth = viewport._maxDepth;
	_minDepth = viewport._minDepth;
}

Viewport::Viewport()
{
	_height = -1;
	_width = -1;
	_maxDepth = -1;
	_minDepth = -1;
}


Viewport::~Viewport()
{
}
