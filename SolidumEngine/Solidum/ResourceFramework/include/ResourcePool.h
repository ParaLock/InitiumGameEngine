#pragma once
#include "../../sysInclude.h"

#include "../include/IResource.h"

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
	IResource* getResource() {

		IResource* res = nullptr;

		if (T::_typePoolValid == false) {

			unsigned int type = IResource::getTypeID(std::type_index(typeid(T)));
			if (type == 0) { IResource::addType(std::type_index(typeid(T))); type = IResource::getTypeID(std::type_index(typeid(T))); }

			ResourcePoolGroup group;

			group._freeResources = new std::list<IResource*>;

			group._typeIndex = _currTypeIndex;

			_currTypeIndex++;

			group._type = type;

			res = new T;

			res->typePoolIndex(group._typeIndex);

			T::_typePoolIndexCompileTime = group._typeIndex;
			T::_typePoolValid = true;

			_resourceList.push_back(group);

			return res;
		}
		else {

			auto& uniqueTypePool = _resourceList.at(T::_typePoolIndexCompileTime);

			if (uniqueTypePool._freeResources->empty()) {

				res = new T;

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
