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

	template<typename T>
	T* getCore() {

		int debugPoint = -1;

		if (dynamic_cast<T*>(this) != NULL) {
			return dynamic_cast<T*>(this);
		}
		else {
			std::cout << "Resource Cast To Core Type failed!" << " " << "RESOURCE NAME:" << std::endl;
		
			return nullptr;
		}
	}
};

