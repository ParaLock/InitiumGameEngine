#pragma once
#include "../../../sysInclude.h"

class GraphicsResourcePool
{
private:
	std::string _poolID;

	std::map<std::string, std::pair<bool, void*>> *_resourceList;
	std::map<std::string, std::pair<bool, void*>>::iterator _itr;
public:
	GraphicsResourcePool(std::string poolID);
	~GraphicsResourcePool();

	void addResource(void *res, std::string resName, bool shared);
	void* getResource(std::string resName);
};

