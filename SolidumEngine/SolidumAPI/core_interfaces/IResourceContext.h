#pragma once

class ResourceInitParams;

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
