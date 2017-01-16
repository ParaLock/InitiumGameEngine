#pragma once
#include "../../../../sysInclude.h"

#include "../../../../ResourceManagement/include/IResourceManager.h"

#include "SolidumObject.h"

class SolidumObjectManager : public IResourceManager
{
public:
	SolidumObjectManager();
	~SolidumObjectManager();

	IResource* createResource(IResourceBuilder* builder, std::string name);
};

