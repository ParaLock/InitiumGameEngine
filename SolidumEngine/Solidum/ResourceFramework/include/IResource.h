#pragma once
#include "../../sysInclude.h"

#include "IResourceBuilder.h"

class IResource
{
private:
protected:
	int _poolIndex;
	volatile bool isLoaded = false;
public:
	IResource();
	virtual ~IResource();

	virtual void load(std::shared_ptr<IResourceBuilder> builder) = 0;
	virtual void unload() = 0;

	virtual void updateParameter(std::string varName, void *data) = 0;
	virtual void* getParameter(std::string varName) = 0;

	bool getLoadStatus() { return isLoaded; }
	int getPoolIndex() { return _poolIndex; }

	void setPoolIndex(int index) { _poolIndex = index; }

	template<typename T>
	T* getCore() {

		if (dynamic_cast<T*>(this) != NULL) {
			return dynamic_cast<T*>(this);
		}
		else {
			std::cout << "Resource Cast To Core Type failed!" << " " << "RESOURCE TYPE:" << typeid(T).name() << std::endl;
		
			throw "BAD CAST";

			//return nullptr;
		}
	}
};

