#pragma once

#include "../../common.h"

class IResource;

class ResourceLookupCache
{
private:
	std::map<std::string, IResource*> _resourceByName;
public:
	ResourceLookupCache();
	~ResourceLookupCache();

	IResource* getResourceByName(std::string& name);
	
	void addResource(std::string& name, IResource* res);
	void removeResource(std::string& name);
};

