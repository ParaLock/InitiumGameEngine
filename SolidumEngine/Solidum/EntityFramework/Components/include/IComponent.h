#pragma once
#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/IEventPublisher.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../EventFramework/include/RenderEvent.h"

#include "../../../GraphicsRendering/RenderOP/include/RenderOP.h"

#include "../../Entity/include/IEntity.h"

enum COMPONENT_TYPE {
	MOVE_COMPONENT,
	RENDER_COMPONENT
};

class IComponent : public IEventListener, public IEventPublisher
{
private:
protected:
public:
	IComponent();
	~IComponent();

	virtual COMPONENT_TYPE getType() = 0;

	virtual void update() = 0;
	virtual void onEvent(EVENT_PTR evt) = 0;

	virtual void setParent(IEntity* parent) = 0;
	virtual IEntity* getParent() = 0;
};

