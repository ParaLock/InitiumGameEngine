#pragma once
#include "../../sysInclude.h"

class IResource;

class PrototypeCache {
private:
	std::map<std::string, std::function<IResource*()>> _prototypesByName;
public:
	void addPrototype(std::string& typeName, std::function<IResource*()> creationfunc);
	void removePrototype(std::string& typeName);
	
	std::function<IResource*()>& getPrototype(std::string& typeName);
};