#pragma once
#include "../../sysInclude.h"

#include "Event.h"

class IEventListener
{
public:
	IEventListener();
	~IEventListener();

	virtual void onEvent(EVENT_PTR evt) = 0;
};

