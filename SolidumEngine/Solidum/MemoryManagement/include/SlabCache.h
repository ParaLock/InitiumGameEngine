#pragma once
#include "../../sysInclude.h"

class Slab {

	friend class SlabCache;

private:

	size_t _size;

	unsigned int _sizeIndex;

public:
	void* _mem;
};

class SlabCache
{
public:

	int _currSizeIndex;

	struct SlabGroup {
		size_t _slabSize;
		unsigned int _sizeIndex;
		std::list<Slab*>* _freeSlabs;
	};

	SlabCache() { _currSizeIndex = 0; };
	~SlabCache() { std::cout << "Slab Cache destruct" << std::endl; };

	void free(Slab* slabPtr);

	Slab* getSlab(size_t size);

private:

	std::vector<SlabGroup> _slabList;
};

