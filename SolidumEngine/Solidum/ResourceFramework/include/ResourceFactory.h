#pragma once
#include "../../sysInclude.h"

template<class resourceType, typename resourceEnum>
class ResourceFactory
{
public:
	ResourceFactory() {};
	~ResourceFactory() {};

	virtual resourceType* createObject(resourceEnum type) = 0;
};

