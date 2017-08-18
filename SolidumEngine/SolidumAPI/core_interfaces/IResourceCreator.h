#pragma once

#include "../common.h"

class IResource;
class ResourceInitParams;

class IResourceCreator {
private:
public:

	virtual IResource* createResourceByPrototypeImmediate(ResourceInitParams* params, std::string name, std::string typeName,
		std::function<void(IResource*)> resLoadedCallback) = 0;

	virtual void createResourceByPrototypeDeferred(ResourceInitParams* params, std::string name, std::string typeName,
		std::function<void(IResource*)> resLoadedCallback) = 0;

	virtual std::unordered_map<std::type_index, unsigned int>& getTypeToTypeIDMap() = 0;
};