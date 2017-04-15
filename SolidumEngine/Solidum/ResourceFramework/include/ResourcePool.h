#pragma once
#include "../../sysInclude.h"

template<class ResourceType, typename EnumType>
class ResourcePool
{
protected:
public:
	ResourcePool() {};
	~ResourcePool() {};

	virtual void allocateResources(EnumType type, int numResources) = 0;

	virtual ResourceType* getResource(EnumType type) = 0;

	virtual void releaseResource(ResourceType* res) = 0;
};

