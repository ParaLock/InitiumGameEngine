#pragma once
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/IEventPublisher.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

enum COMPONENT_TYPE {
	MOVE_COMPONENT,
	RENDER_COMPONENT
};

class IComponent : public IEventListener, public IEventPublisher
{
private:
protected:
	COMPONENT_TYPE _type;
public:
	IComponent();
	~IComponent();

	COMPONENT_TYPE getType() { return _type; }

	virtual void update() = 0;

	virtual void onEvent(IEvent* evt) = 0;
};

