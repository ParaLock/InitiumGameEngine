#include "../include/ShaderUniformGroup.h"



ShaderUniformGroup::ShaderUniformGroup() : _uniformCache(nullptr)
{
}


ShaderUniformGroup::~ShaderUniformGroup()
{
	for each(Uniform slab in _uniformList) {
		_uniformCache->free(slab._data);
	}

	_uniformList.clear();
}
