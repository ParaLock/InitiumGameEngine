#include "../include/SlabCache.h"

void SlabCache::free(Slab* slabPtr) {

	_slabList.at(slabPtr->_sizeIndex)._freeSlabs->push_back(slabPtr);

	ZeroMemory(slabPtr->_mem, slabPtr->_size);
}


Slab* SlabCache::getSlab(size_t size) {

	Slab* slab = nullptr;

	//Check slab for size
	for each(auto& uniqueSize in _slabList) {

		//Proper slab size found
		if (uniqueSize._slabSize == size) {

			//No slabs are free
			if (uniqueSize._freeSlabs->empty()) {

				slab = new Slab;

				slab->_sizeIndex = uniqueSize._sizeIndex;
				slab->_size = size;

				slab->_mem = malloc(size);

				return slab;

			}
			//There are free slabs of given size
			else {

				slab = uniqueSize._freeSlabs->back();
				uniqueSize._freeSlabs->pop_back();

				return slab;
			}
		}
	}

	//No proper size group was found
	SlabGroup group;

	group._freeSlabs = new std::list<Slab*>;

	group._sizeIndex = _currSizeIndex;

	_currSizeIndex++;

	group._slabSize = size;

	slab = new Slab;

	slab->_sizeIndex = group._sizeIndex;
	slab->_size = size;

	slab->_mem = malloc(size);

	_slabList.push_back(group);

	return slab;
}