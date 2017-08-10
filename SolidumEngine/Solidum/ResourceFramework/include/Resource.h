#pragma once
#include "../../sysInclude.h"

#include "ResourceContext.h"
#include "ResourcePool.h"
#include "ResourceSignature.h"

#include "../../../SolidumAPI/core_objects/include/ResourceInitParams.h"
#include "../../../SolidumAPI/core_interfaces/IEngineInstance.h"

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
class Resource : public IResource
{
	friend class ResourcePool;
private:

	IResourceContext* _context = nullptr;

	std::string _name;

	ResourceSignature _type;

	unsigned int _typePoolIndexRuntime;

	static unsigned int _typePoolIndexCompileTime;


protected:
	IResourceContext* getContext() {

		if (_context == nullptr) {

			_context = new ResourceContext<T_RESOURCE>();

			return _context;
		}

		return _context;
	}

public:
	Resource()
	{
		_typePoolIndexRuntime = 0;
	}
	~Resource() {

	}

	static bool _typePoolValid;

	typedef T_POOL POOL;
	typedef T_FACTORY Factory;

	static POOL _pool;

	virtual void load() = 0;
	virtual void unload() = 0;

	void release() {

		unload();

		_pool.releaseResource(this);
	}

	virtual void updateParameter(std::string varName, void *data) {};
	virtual void* getParameter(std::string varName) { return nullptr; };
	
	std::string name() { return _name; }
	void name(std::string newName) { _name = newName; }	

	unsigned int typePoolIndex() { return _typePoolIndexRuntime; }
	void typePoolIndex(unsigned int index) { _typePoolIndexRuntime = index; }

	unsigned int type() { return _type._typeid;};
	void type(unsigned int type) { _type._typeid = type; }
};

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
T_POOL Resource<T_RESOURCE, T_FACTORY, T_POOL>::_pool;

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
unsigned int Resource<T_RESOURCE, T_FACTORY, T_POOL>::_typePoolIndexCompileTime = 0;

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
bool Resource<T_RESOURCE, T_FACTORY, T_POOL>::_typePoolValid = false;