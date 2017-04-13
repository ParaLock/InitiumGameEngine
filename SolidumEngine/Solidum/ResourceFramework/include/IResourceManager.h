#pragma once
#include "../../sysInclude.h"

#include "../include/ResourcePool.h"

#include "IResourceBuilder.h"
#include "IResource.h"

class IResourceManager
{
protected:
	std::map<std::string, IResource*> *_activeResources;
public:
	IResourceManager();
	~IResourceManager();

	virtual IResource* createResource(std::shared_ptr<IResourceBuilder> builder, std::string name, bool loadAsync) = 0;

	void addResource(IResource* res, std::string name);

	IResource* getResource(std::string name);

	std::map<std::string, IResource*>* getResourceMap() { return _activeResources; };
};
