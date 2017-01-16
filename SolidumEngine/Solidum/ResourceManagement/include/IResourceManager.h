#pragma once
#include "../../sysInclude.h"

#include "IResourceBuilder.h"
#include "IResource.h"

class IResourceManager
{
protected:
	std::map<std::string, IResource*> *_activeResources;
public:
	IResourceManager();
	~IResourceManager();

	virtual IResource* createResource(IResourceBuilder* builder, std::string name) = 0;

	void addResource(IResource* res, std::string name);

	IResource* getResource(std::string name);

	std::map<std::string, IResource*>* getResourceMap() { return _activeResources; };
};
