#pragma once
#include "../../sysInclude.h"

class SlabCache
{
public:
	class Slab {

		friend class SlabCache;

	private:

		size_t _size;

		bool _isFree;

		Slab* _next = nullptr;

	public:
		void* _mem;
	};

	SlabCache(int burstAllocationDepth) {
		_burstAlloctionDepth = burstAllocationDepth;
	}

	~SlabCache() {};

	void free(Slab* slabPtr) {

		slabPtr->_isFree = true;

		ZeroMemory(slabPtr->_mem, slabPtr->_size);
	}

	Slab* getSlab(size_t size) {
	
		auto& itr = _rootSizes.begin();

		bool sizeFound = false;
		bool nonFree = true;

		Slab* _slab;

		while (itr != _rootSizes.end()) {

			_slab = *itr;

			if (_slab->_size == size) {

				sizeFound = true;

				while (_slab->_next != nullptr) {
					if (_slab->_isFree) {

						nonFree = false;

						return _slab;
					}

					_slab = _slab->_next;
				}
			}

			itr++;
		}

		if (!sizeFound) {

			Slab* newBaseSlab = new Slab();

			newBaseSlab->_isFree = false;
			newBaseSlab->_next = nullptr;
			newBaseSlab->_size = size;
			newBaseSlab->_mem = malloc(size);

			_rootSizes.push_back(newBaseSlab);

			return newBaseSlab;
		}

		if (nonFree) {

			Slab* newSlab = new Slab();

			newSlab->_isFree = false;
			newSlab->_next = nullptr;
			newSlab->_size = size;
			newSlab->_mem = malloc(size);

			_slab->_next = newSlab;

			return newSlab;
		}
		return nullptr;
	}

private:

	int _burstAlloctionDepth;

	std::list<Slab*> _rootSizes;
};

