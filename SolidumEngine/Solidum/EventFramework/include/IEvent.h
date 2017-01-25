#pragma once
#include "../../sysInclude.h"

enum EVENT_TYPE {
	INPUT_EVENT,
	RENDER_EVENT,
	ENTITY_EVENT
};

class IEvent
{
private:
	EVENT_TYPE _type;
public:
	IEvent();
	~IEvent();

	EVENT_TYPE getType() { return _type; }
	void setType(EVENT_TYPE type) { _type = type; }

	template<typename T>
	T* getEvent() {

		int debugPoint = -1;

		if (static_cast<T*>(this) != NULL) {
			return static_cast<T*>(this);
		}
		else {
			std::cout << "Event Cast To Type failed!" << std::endl;

			return nullptr;
		}
	}
};

