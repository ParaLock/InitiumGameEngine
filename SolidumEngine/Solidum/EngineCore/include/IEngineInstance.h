#pragma once
#include "../../sysInclude.h"

class ResourceLookupCache;

class IEngineInstance
{
public:
	IEngineInstance();
	~IEngineInstance();

	virtual ResourceLookupCache* getResourceLookupCache(std::string& resourceGroup) = 0;
};

