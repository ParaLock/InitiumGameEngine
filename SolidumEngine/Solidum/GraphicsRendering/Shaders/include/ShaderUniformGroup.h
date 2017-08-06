#pragma once
#include "../../../sysInclude.h"

#include "../../../MemoryManagement/include/SlabCache.h"

class ShaderUniformGroup
{
public:
	ShaderUniformGroup();
	~ShaderUniformGroup();

	ShaderUniformGroup(ShaderUniformGroup& other) {
		
		_uniformCache = other._uniformCache;
		_uniformList = other._uniformList;

		other._uniformList.clear();
		other._uniformCache = nullptr;
	}

	ShaderUniformGroup& operator=(ShaderUniformGroup& other) {

		_uniformList = other._uniformList;
		_uniformCache = other._uniformCache;

		other._uniformList.clear();
		other._uniformCache = nullptr;

		return *this;
	}

	struct Uniform {

		Uniform(std::string& name, Slab* data) {
			_name = name;
			_data = data;
		}

		std::string _name;
		Slab* _data;

	};

	void setUniformCache(SlabCache* cache) { _uniformCache = cache; }

	template<typename T>
	void addUniform(T& data, std::string name) {

		Slab* dataSlab = _uniformCache->getSlab(sizeof(T));

		*(T*)dataSlab->_mem = data;

		_uniformList.push_back(Uniform(name, dataSlab));
	}
	std::list<Uniform>& getUniforms() { return _uniformList; };

	void reset();

private:

	SlabCache* _uniformCache;

	std::list<Uniform> _uniformList;
};

