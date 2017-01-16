#include "../include/ResourceManagerPool.h"



ResourceManagerPool::ResourceManagerPool()
{
	_managerPool = new std::map<std::string, IResourceManager*>;
}


ResourceManagerPool::~ResourceManagerPool()
{
	delete _managerPool;
}

void ResourceManagerPool::registerResourceManager(IResourceManager* manager, std::string name)
{
	auto itr = _managerPool->find(name);

	if (itr == _managerPool->end()) {
		_managerPool->insert({ name, manager });
	}
}

IResourceManager * ResourceManagerPool::getResourceManager(std::string name)
{
	auto itr = _managerPool->find(name);

	if (itr != _managerPool->end()) {

		return _managerPool->at(name);
	}
	else {
		std::cout << "Resource Manager Not Found! :(" << " " << "RESOURCE MANAGER NAME:" << name << std::endl;
	}

	return nullptr;
}
