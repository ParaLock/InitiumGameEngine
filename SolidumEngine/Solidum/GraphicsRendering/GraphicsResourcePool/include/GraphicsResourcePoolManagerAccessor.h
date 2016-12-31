#pragma once
#include "../include/GraphicsResourcePoolManager.h"

class GraphicsResourcePoolManagerAccessor
{
public:
	GraphicsResourcePoolManagerAccessor();
	~GraphicsResourcePoolManagerAccessor();

	static GraphicsResourcePoolManager* poolManager;

	static void initAccessor(GraphicsResourcePoolManager* activeInstance) { poolManager = activeInstance; };
};

