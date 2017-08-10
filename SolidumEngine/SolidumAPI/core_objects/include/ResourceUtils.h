#pragma once

#include "../../core_interfaces/IResource.h"
#include "../../core_interfaces/IEngineInstance.h"
#include "../../core_interfaces/IResourceCreator.h"

class ResourceUtils
{
private:
public:
	ResourceUtils();
	~ResourceUtils();

	static IResource* lookupResource(std::string& name, std::string& group, IEngineInstance* sysInstance);

	static void createResourceGroup(std::string& groupName, IEngineInstance* sysInstance);
	static void addResourceToGroup(IResource* res, std::string& groupName, IEngineInstance* sysInstance);

	static unsigned int getTypeID(std::type_index index, IResourceCreator* creator);
	static void addType(std::type_index index, IResourceCreator* creator);

};

