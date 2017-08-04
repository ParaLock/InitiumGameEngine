#pragma once
#include "../../sysInclude.h"

#include "../../EngineCore/include/IEngineInstance.h"

#include "IResource.h"
#include "ResourceInitParams.h"
#include "ResourceContext.h"
#include "ResourcePool.h"
#include "ResourceSignature.h"

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
class Resource : public IResource
{
private:

	int _poolIndex;

	IResourceContext* _context = nullptr;

	std::string _name;

	ResourceSignature _type;

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

	}
	~Resource() {

	}

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

	unsigned int poolIndex() { return _poolIndex; }
	void poolIndex(unsigned int index) { _poolIndex = index; }

	unsigned int type() { return _type._typeid;};
	void type(unsigned int type) { _type._typeid = type; }
};

template<typename T_RESOURCE, typename T_FACTORY, typename T_POOL>
T_POOL Resource<T_RESOURCE, T_FACTORY, T_POOL>::_pool;
