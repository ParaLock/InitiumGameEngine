#pragma once

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../GraphicsRendering/GraphicsCore/include/GraphicsCore.h"

#include "../../Entity/include/IEntity.h"

#include "IComponent.h"

class Component : public IComponent, public IResource
{
private:
protected:
	COMPONENT_TYPE _type;

	IEntity* _parent = nullptr;

	void setType(COMPONENT_TYPE type) { _type = type; };
public:
	Component();
	~Component();

	COMPONENT_TYPE getType() { return _type; }

	virtual void update() = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }
};

