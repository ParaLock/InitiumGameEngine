#pragma once
#include "../../../sysInclude.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../Components/include/IComponent.h"

class Entity
{
private:
	std::list<Entity*>* _children;
	std::list<IComponent*>* _components;

	Transform* _transform;
public:
	Entity();
	~Entity();

	void addComponent(IComponent* comp);

	Transform* getTransform() { return _transform; };

	void update();
};

