#include "../include/IResource.h"



IResource::IResource()
{
}


IResource::~IResource()
{
}

IResource * IResource::lookupResource(std::string & name, std::string & group, IEngineInstance * sysInstance)
{
	IResource* res = nullptr;

	ResourceLookupCache* cache = sysInstance->getResourceLookupCache(group);

	res = cache->getResourceByName(name);

	return res;
	
}

void IResource::createResourceGroup(std::string & groupName, IEngineInstance * sysInstance)
{
	sysInstance->getResourceLookupCache(groupName);
}

void IResource::addResourceToGroup(IResource* res, std::string & groupName, IEngineInstance * sysInstance)
{
	ResourceLookupCache* cache = sysInstance->getResourceLookupCache(groupName);

	if (cache) {

		cache->addResource(res->name(), res);

	}
}

unsigned int IResource::getTypeID(std::type_index index)
{
	auto& itr = _typeIDByTypeIndex.find(index);

	if (itr != _typeIDByTypeIndex.end()) {
		return _typeIDByTypeIndex.at(index);
	}
	else {
		return 0;
	}
}

void IResource::addType(std::type_index index)
{
	_typeIDByTypeIndex.insert({ index, getRandomNumber() });
}

std::unordered_map<std::type_index, unsigned int> IResource::_typeIDByTypeIndex;
