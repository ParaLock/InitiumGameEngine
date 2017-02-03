#pragma once
#pragma once
#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../EventFramework/include/RenderEvent.h"

#include "../../../GraphicsRendering/RenderOP/include/RenderOP.h"

#include "IComponent.h"

#include "../../Entity/include/IEntity.h"

class Component : public IComponent
{
private:
protected:
	COMPONENT_TYPE _type;

	IEntity* _parent = nullptr;
public:
	Component();
	~Component();

	COMPONENT_TYPE getType() { return _type; }

	virtual void update() = 0;
	virtual void onEvent(EVENT_PTR evt) = 0;

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }
};

