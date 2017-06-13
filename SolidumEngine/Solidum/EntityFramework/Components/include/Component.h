#pragma once

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../GraphicsRendering/GraphicsCore/include/IGraphicsCore.h"

#include "../../../GraphicsRendering/EntityRenderObject/include/IEntityRenderObject.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataPacket.h"

#include "../../../ResourceFramework/include/IResource.h"

#include "IComponent.h"

class Component : public IResource, public IComponent
{
private:
protected:
	int _index = -1;

	COMPONENT_TYPE _type;

	IEntity* _parent = nullptr;

	void setType(COMPONENT_TYPE type) { _type = type; };
public:
	Component();
	~Component();

	COMPONENT_TYPE getType() { return _type; }

	virtual void update(float delta) = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }

	virtual std::shared_ptr<RenderDataPacket> createRenderData() = 0;
};

