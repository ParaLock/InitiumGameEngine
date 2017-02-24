#pragma once
#include "../../sysInclude.h"

enum EVENT_TYPE {
	INPUT_EVENT,
	ENTITY_EVENT,
	PHYSICS_EVENT,
	GRAPHICS_EVENT
};

enum SUB_EVENT_TYPE {
	REGISTER_RENDER_NODE,
	UNREGISTER_RENDER_NODE,
};

class IEvent
{
protected:
	EVENT_TYPE _type;
	SUB_EVENT_TYPE _subType;
public:
	IEvent();
	~IEvent();

	EVENT_TYPE getType() { return _type; }

	template<typename T>
	T* getEvent() {

		int debugPoint = -1;

		if (static_cast<T*>(this) != NULL) {
			return static_cast<T*>(this);
		}
		else {
			std::cout << "Event Cast To Type failed!" << std::endl;

			throw "BAD CAST";
		}
	}
};

