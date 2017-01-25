#include "../include/Entity.h"



Entity::Entity()
{
	_transform = new Transform;
	_components = new std::list<IComponent*>;
	_children = new std::list<Entity*>;
}


Entity::~Entity()
{
	delete _transform;
	delete _components;
	delete _children;
}

void Entity::addComponent(IComponent * comp)
{
	_components->push_back(comp);
}

void Entity::update()
{
	for (auto itr = _components->begin(); itr != _components->end(); itr++) {
		
		IComponent* comp = *itr;
		
		comp->update();
	}

	for (auto itr = _children->begin(); itr != _children->end(); itr++) {

		Entity* child = *itr;

		child->update();
	}
}
