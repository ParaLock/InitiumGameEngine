#pragma once
#include "GraphicsResourcePool.h"

class GPUBuffer;
class RenderTarget;

class GraphicsResourcePoolManager
{
private:
	std::map<std::string, GraphicsResourcePool*> *_activePoolList;
public:
	GraphicsResourcePoolManager();
	~GraphicsResourcePoolManager();

	void createNewResourcePool(std::string poolID);

	GraphicsResourcePool *getPool(std::string poolID);
};

