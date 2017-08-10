#pragma once
#include "../../Solidum/sysInclude.h"

class ResourceLookupCache;
class PrototypeCache;

class IEngineInstance
{
public:
	IEngineInstance() {};
	~IEngineInstance() {};

	virtual ResourceLookupCache* getResourceLookupCache(std::string& resourceGroup) = 0;
	virtual PrototypeCache& getResourcePrototypeCache() = 0;
};

