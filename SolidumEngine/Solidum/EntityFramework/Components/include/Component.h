#pragma once

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../../GraphicsRendering/GraphicsCore/include/IGraphicsCore.h"

#include "../../../GraphicsRendering/EntityRenderObject/include/IEntityRenderObject.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataPacket.h"

#include "../../../ResourceFramework/include/Resource.h"

#include "../../../ResourceFramework/include/GenericFactory.h"

#include "IComponent.h"

class ResourcePool;

class Component : public IComponent, public Resource<Component, GenericFactory, ResourcePool>
{
private:
protected:
	int _index = -1;

	IEntity* _parent = nullptr;
public:
	Component();
	~Component();

	struct InitData {

	};

	virtual void update(float delta) = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	void setParent(IEntity* parent) { _parent = parent; };
	IEntity* getParent() { return _parent; }

	virtual void AddRenderData(RenderDataGroup* collection) = 0;
};

