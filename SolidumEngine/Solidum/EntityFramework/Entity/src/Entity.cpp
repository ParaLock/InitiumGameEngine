#include "../include/Entity.h"



Entity::Entity()
{
	_renderObject = new EntityRenderObject();

	_transform = new Transform;
	_children = new std::list<IEntity*>;
}


Entity::~Entity()
{
	delete _transform;
	delete _children;
}

void Entity::addChild(IEntity * entity)
{
	entity->setParent(this);

	_children->push_back(entity);
}
void Entity::setParent(IEntity * parent)
{
	_parent = parent; 
	
	_transform->setParent(_parent->getTransform());
}

void Entity::update(float delta, RenderDataGroup* collection)
{
	_renderObject->attachRenderDataToGroup(collection);

	for (auto itr = _components.begin(); itr != _components.end(); itr++) {
		
		for (auto compItr = _components.at(itr->first).begin();
			 compItr != _components.at(itr->first).end(); compItr++) {

			IComponent* comp = *compItr;

			comp->update(delta);
		}
	}

	for (auto itr = _children->begin(); itr != _children->end(); itr++) {

		IEntity* child = *itr;

		child->setWorld(_parentWorld);

		child->update(delta, collection);
	}
}
