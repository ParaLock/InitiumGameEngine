#include "../include/IResourceManager.h"

IResourceManager::IResourceManager()
{
	_activeResources = new std::map<std::string, IResource*>;
}

IResourceManager::~IResourceManager()
{
	for (auto itr = _activeResources->begin(); itr != _activeResources->end(); itr++) {
		IResource* res = itr->second;

		delete res;
	}

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
