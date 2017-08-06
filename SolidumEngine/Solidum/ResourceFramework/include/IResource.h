#pragma once
#include "../../sysInclude.h"

#include "../../EngineCore/include/IEngineInstance.h"

#include "ResourceLookupCache.h"

class IResourceContext;

class IResource
{
private:
	static std::unordered_map<std::type_index, unsigned int> _typeIDByTypeIndex;
public:
	IResource();
	~IResource();

	static IResource* lookupResource(std::string& name, std::string& group, IEngineInstance* sysInstance);

	static void createResourceGroup(std::string& groupName, IEngineInstance* sysInstance);
	static void addResourceToGroup(IResource* res, std::string& groupName, IEngineInstance* sysInstance);

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void typePoolIndex(unsigned int index) = 0;
	virtual unsigned int typePoolIndex() = 0;

	virtual IResourceContext* getContext() = 0;

	virtual std::string name() = 0;
	virtual void name(std::string newName) = 0;

	virtual unsigned int type() = 0;
	virtual void type(unsigned int type) = 0;

	static unsigned int getTypeID(std::type_index index);
	static void addType(std::type_index index);

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void release() = 0;
};

