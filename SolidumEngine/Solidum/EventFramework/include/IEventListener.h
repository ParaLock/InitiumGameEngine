#pragma once
#include "../../sysInclude.h"

#include "IEvent.h"

class IEventListener
{
public:
	IEventListener();
	~IEventListener();

	virtual void onEvent(IEvent* evt) = 0;
};

