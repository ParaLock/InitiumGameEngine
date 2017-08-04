#pragma once
#include "../../sysInclude.h"

#include "ResourceInitParams.h"

class IResourceContext {
public:

	IResourceContext() {}

	virtual void setResourceInitParams(ResourceInitParams* params) = 0;
	virtual ResourceInitParams* getResourceInitParams() = 0;

	virtual void attachLoadDependancy(std::function<bool()> loadDependancy) = 0;
	virtual void attachUnloadDependancy(std::function<bool()> unloadDependancy) = 0;

	virtual bool isLoadable() = 0;
	virtual bool isUnloadable() = 0;

	virtual void setLoadState(bool state) = 0;
	virtual bool getLoadState() = 0;
private:
};

template<typename T_RESOURCE>
class ResourceContext : public IResourceContext {
private:

	bool _isLoaded;

	std::list<std::function<bool()>> _activeLoadDependancies;
	std::list<std::function<bool()>> _activeUnloadDependancies;
protected:
	typename T_RESOURCE::InitData _INIT_PARAMS;
public:

	ResourceContext() { }
	~ResourceContext() {}

	void* getResourceInitParamsRawPtr() { return &_INIT_PARAMS; }

	void setResourceInitParams(ResourceInitParams* params) { _INIT_PARAMS = *(typename T_RESOURCE::InitData*)params; }
	ResourceInitParams* getResourceInitParams() { return (ResourceInitParams*)&_INIT_PARAMS; }

	void attachLoadDependancy(std::function<bool()> loadDependancy) {};
	void attachUnloadDependancy(std::function<bool()> unloadDependancy) {};

	bool isLoadable() { return true; };
	bool isUnloadable() { return true; };

	void setLoadState(bool state) { _isLoaded = state; }
	bool getLoadState() { return _isLoaded; }
};