#include "../include/ResourceLookupCache.h"



ResourceLookupCache::ResourceLookupCache()
{
}


ResourceLookupCache::~ResourceLookupCache()
{
}

IResource * ResourceLookupCache::getResourceByName(std::string & name)
{
	IResource* resource = nullptr;

	auto& itr = _resourceByName.find(name);

	if (itr != _resourceByName.end()) {
		resource = _resourceByName.at(name);
	}

	return resource;
}

void ResourceLookupCache::addResource(std::string & name, IResource * res)
{
	_resourceByName.insert({name, res});

}

void ResourceLookupCache::removeResource(std::string & name)
{
	auto& itr = _resourceByName.find(name);

	if (itr != _resourceByName.end()) {
		_resourceByName.erase(itr);
	}

	return;
}
