#pragma once

class GraphicsCore;

class GraphicsCoreAccessor
{
public:
	GraphicsCoreAccessor();
	~GraphicsCoreAccessor();

	static void initAccessor(GraphicsCore* core);

	static GraphicsCore* activeGraphicsCore;
};

