#include "../include/PrototypeCache.h"

void PrototypeCache::addPrototype(std::string & typeName, std::function<IResource*()> creationfunc)
{
	_prototypesByName.insert({typeName, creationfunc});
}

void PrototypeCache::removePrototype(std::string& typeName)
{
	_prototypesByName.erase(typeName);
}

std::function<IResource*()>& PrototypeCache::getPrototype(std::string & typeName)
{
	return _prototypesByName.at(typeName);
}
