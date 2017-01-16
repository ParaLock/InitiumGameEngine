#pragma once
#include "IResourceManager.h"

class ResourceManagerPool
{
private:
	std::map<std::string, IResourceManager*> *_managerPool;
public:
	ResourceManagerPool();
	~ResourceManagerPool();

	void registerResourceManager(IResourceManager* manager, std::string name);

	IResourceManager* getResourceManager(std::string name);

	template<typename T>
	T* getResourceManagerSpecific(std::string name) {
		auto itr = _managerPool->find(typeid(T).name());

		if (itr != _managerPool->end()) {

			if (dynamic_cast<T*>(_managerPool->at(name)) != NULL) {
				return dynamic_cast<T*>(_managerPool->at(name));
			}
			else {
				std::cout << "Resource Manager Cast To Core Type failed!" << " " << "RESOURCE MANAGER NAME:" << name << std::endl;

				return nullptr;
			}
		}
		else {
			std::cout << "Resource Manager Not Found! :(" << " " << "RESOURCE MANAGER NAME:" << name << std::endl;
		}
	}
};

