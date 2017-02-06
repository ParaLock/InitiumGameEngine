#pragma once
#include "../../sysInclude.h"

#include "IResourceBuilder.h"

class IResource
{
private:
protected:
	volatile bool isLoaded = false;
public:
	IResource();
	virtual ~IResource();

	virtual void load(IResourceBuilder *builder) = 0;

	virtual void unload() = 0;

	bool getLoadStatus() { return isLoaded; };

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

