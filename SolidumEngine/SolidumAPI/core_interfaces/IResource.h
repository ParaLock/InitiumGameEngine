#pragma once
#include "../../Solidum/sysInclude.h"

#include "IEngineInstance.h"

#include "../core_objects/include/ResourceLookupCache.h"

class IResourceContext;

class IResource
{
private:
public:
	IResource() {};
	~IResource() {};

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	virtual void typePoolIndex(unsigned int index) = 0;
	virtual unsigned int typePoolIndex() = 0;

	virtual IResourceContext* getContext() = 0;

	virtual std::string name() = 0;
	virtual void name(std::string newName) = 0;

	virtual unsigned int type() = 0;
	virtual void type(unsigned int type) = 0;

	virtual void load() = 0;
	virtual void unload() = 0;

	virtual void release() = 0;
};

