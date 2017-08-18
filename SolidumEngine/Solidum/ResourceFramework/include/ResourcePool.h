#pragma once
#include "../../sysInclude.h"

#include "../../../SolidumAPI/core_interfaces/IResource.h"

#include "../../../SolidumAPI/core_objects/include/ResourceUtils.h"

class IResourceCreator;

class ResourcePool {
private:

	struct ResourcePoolGroup {
		unsigned int _typeIndex;
		unsigned int _type;
		std::list<IResource*>* _freeResources;
	};

	unsigned int _currTypeIndex;

	std::vector<ResourcePoolGroup> _resourceList;

public:

	ResourcePool() : _currTypeIndex(0) {}

	template<typename T>
	IResource* getResource(IResourceCreator* creator, std::function<IResource*()> createFunc) {

		IResource* res = nullptr;

		if (T::_typePoolValid == false) {

			unsigned int type = ResourceUtils::getTypeID(std::type_index(typeid(T)), creator);
			if (type == 0) { ResourceUtils::addType(std::type_index(typeid(T)), creator); type = ResourceUtils::getTypeID(std::type_index(typeid(T)), creator); }

			ResourcePoolGroup group;

			group._freeResources = new std::list<IResource*>;

			group._typeIndex = _currTypeIndex;

			_currTypeIndex++;

			group._type = type;

			if (createFunc) {
				res = createFunc();
			}
			else {
				res = new T;
			}

			res->typePoolIndex(group._typeIndex);

			T::_typePoolIndexCompileTime = group._typeIndex;
			T::_typePoolValid = true;

			_resourceList.push_back(group);

			return res;
		}
		else {

			auto& uniqueTypePool = _resourceList.at(T::_typePoolIndexCompileTime);

			if (uniqueTypePool._freeResources->empty()) {

				if (createFunc) {
					res = createFunc();
				}
				else {
					res = new T;
				}

				res->typePoolIndex(uniqueTypePool._typeIndex);

				return res;

			}
			else {

				res = uniqueTypePool._freeResources->back();
				uniqueTypePool._freeResources->pop_back();

				return res;
			}

		}
	}

	void releaseResource(IResource* res) {
	
		_resourceList.at(res->typePoolIndex())._freeResources->push_back(res);
	
	}
};
