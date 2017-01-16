#include "../include/GraphicsCoreAccessor.h"

GraphicsCore* GraphicsCoreAccessor::activeGraphicsCore = nullptr;

GraphicsCoreAccessor::GraphicsCoreAccessor()
{
}


GraphicsCoreAccessor::~GraphicsCoreAccessor()
{
}

void GraphicsCoreAccessor::initAccessor(GraphicsCore * core)
{
	activeGraphicsCore = core;
}
