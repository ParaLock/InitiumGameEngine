#include "../include/ResourceUtils.h"



ResourceUtils::ResourceUtils()
{
}


ResourceUtils::~ResourceUtils()
{
}

IResource * ResourceUtils::lookupResource(std::string & name, std::string & group, IEngineInstance * sysInstance)
{
	IResource* res = nullptr;

	ResourceLookupCache* cache = sysInstance->getResourceLookupCache(group);

	res = cache->getResourceByName(name);

	return res;

}

void ResourceUtils::createResourceGroup(std::string & groupName, IEngineInstance * sysInstance)
{
	sysInstance->getResourceLookupCache(groupName);
}

void ResourceUtils::addResourceToGroup(IResource* res, std::string & groupName, IEngineInstance * sysInstance)
{
	ResourceLookupCache* cache = sysInstance->getResourceLookupCache(groupName);

	if (cache) {

		cache->addResource(res->name(), res);

	}
}

unsigned int ResourceUtils::getTypeID(std::type_index index, IResourceCreator* creator)
{
	auto& idMap = creator->getTypeToTypeIDMap();

	auto& itr = idMap.find(index);

	if (itr != idMap.end()) {
		return idMap.at(index);
	}
	else {
		return 0;
	}
}

void ResourceUtils::addType(std::type_index index, IResourceCreator* creator)
{
	creator->getTypeToTypeIDMap().insert({ index, getRandomNumber() });
}
