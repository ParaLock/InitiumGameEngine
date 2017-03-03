#include "../include/World.h"



World::World()
{
}


World::~World()
{
}

void World::addPrimaryCamera(IEntity * camera, uint64_t id)
{
	_primaryCameraID = id;

	_entities.insert({ id, camera });
}

void World::addEntity(IEntity * entity, uint64_t entityID)
{
	_entities.insert({ entityID, entity});
}

void World::removeEntity(uint64_t entityID)
{
}

IEntity * World::getEntity(uint64_t entityID)
{
	return _entities.at(entityID);
}

const std::map<uint64_t, IEntity*>& World::getEntities()
{
	return _entities;
}
