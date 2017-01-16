#include "../include/IResourceManager.h"

IResourceManager::IResourceManager()
{
	_activeResources = new std::map<std::string, IResource*>;
}

IResourceManager::~IResourceManager()
{
	delete _activeResources;
}

void IResourceManager::addResource(IResource * res, std::string name)
{
	auto itr = _activeResources->find(name);

	if (itr == _activeResources->end()) {
		_activeResources->insert({name, res});
	}
}

IResource* IResourceManager::getResource(std::string name)
{
	auto itr = _activeResources->find(name);

	if (itr != _activeResources->end()) {
		return _activeResources->at(name);
	}

	return nullptr;
}
