#include "../include/Entity.h"



Entity::Entity()
{
	_transform = new Transform;
	_components = new std::list<IComponent*>;
	_children = new std::list<IEntity*>;
}


Entity::~Entity()
{
	delete _transform;
	delete _components;
	delete _children;
}

void Entity::addComponent(IComponent * comp)
{
	comp->setParent(this);

	_components->push_back(comp);
}

void Entity::addChild(IEntity * entity)
{
	entity->setParent(this);

	_children->push_back(entity);
}

void Entity::update()
{

	if (_parent != nullptr) 
		_transform->setPos(_parent->getTransform()->getPos());

	for (auto itr = _components->begin(); itr != _components->end(); itr++) {
		
		IComponent* comp = *itr;
		
		comp->update();
	}

	for (auto itr = _children->begin(); itr != _children->end(); itr++) {

		IEntity* child = *itr;

		child->update();
	}

}
