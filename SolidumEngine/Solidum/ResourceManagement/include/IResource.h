#pragma once
#include "../../sysInclude.h"

class IResource
{
private:
public:
	IResource();
	virtual ~IResource();

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

