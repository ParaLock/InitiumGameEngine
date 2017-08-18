#pragma once

#include "../common.h"

class ResourceLookupCache;
class PrototypeCache;
class IGraphicsCore;

class IEngineInstance
{
public:
	IEngineInstance() {};
	~IEngineInstance() {};

	virtual ResourceLookupCache* getResourceLookupCache(std::string& resourceGroup) = 0;
	virtual PrototypeCache& getResourcePrototypeCache() = 0;

	virtual IGraphicsCore* getGraphicsSubsystem() = 0;
};

