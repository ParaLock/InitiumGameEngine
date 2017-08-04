#include "../include/SlabCache.h"

void SlabCache::free(Slab* slabPtr) {

	slabPtr->_isFree = true;

	ZeroMemory(slabPtr->_mem, slabPtr->_size);
}


Slab* SlabCache::getSlab(size_t size) {

	auto& itr = _rootSizes.find(size);

	if (itr != _rootSizes.end()) {
		//Size found, look for free slab
		auto& slabList = itr->second;

		for each(Slab* slab in slabList) {

			if (slab->_isFree) {

				slab->_isFree = false;

				return slab;
			}
		}

		Slab* newSlab = new Slab;

		newSlab->_mem = malloc(size);
		newSlab->_isFree = false;
		newSlab->_size = size;

		slabList.push_back(newSlab);

		return newSlab;
	}
	else {

		Slab* newSlab = new Slab;

		newSlab->_mem = malloc(size);
		newSlab->_isFree = false;
		newSlab->_size = size;

		std::list<Slab*> newSlabList;

		newSlabList.push_back(newSlab);

		_rootSizes.insert({size, newSlabList });

		return newSlab;
	}

	return nullptr;
}