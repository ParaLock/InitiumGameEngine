#pragma once
#include "../../sysInclude.h"

class Slab {

	friend class SlabCache;

private:

	size_t _size;

	bool _isFree;

public:
	void* _mem;
};

class SlabCache
{
public:

	SlabCache() {};
	~SlabCache() { std::cout << "Slab Cache destruct" << std::endl; };

	void free(Slab* slabPtr);

	Slab* getSlab(size_t size);

private:

	std::unordered_map<size_t, std::list<Slab*>> _rootSizes;
};

