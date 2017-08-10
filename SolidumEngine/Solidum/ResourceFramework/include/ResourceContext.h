#pragma once
#include "../../sysInclude.h"

#include "../../../SolidumAPI/core_objects/include/ResourceInitParams.h"
#include "../../../SolidumAPI/core_interfaces/IResourceContext.h"

template<typename T_RESOURCE>
class ResourceContext : public IResourceContext {
private:

	bool _isLoaded;

	std::list<std::function<bool()>> _activeLoadDependancies;
	std::list<std::function<bool()>> _activeUnloadDependancies;
protected:
	typename T_RESOURCE::InitData _INIT_PARAMS;
public:

	ResourceContext() {}
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