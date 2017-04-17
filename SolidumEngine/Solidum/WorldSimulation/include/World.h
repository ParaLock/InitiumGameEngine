#pragma once
#include "../../sysInclude.h"
#include "../../PhysicsFramework/include/BoundingSphere.h"
#include "../../EntityFramework/Entity/include/Entity.h"

class WorldAttributes {

};

class World
{
private:
	uint64_t _primaryCameraID;

	std::map<uint64_t, IEntity*> _entities;

	BoundingSphere* _boundingSphere;
public:
	World();
	~World();

	void addPrimaryCamera(IEntity* camera, uint64_t id);

	void addEntity(IEntity* entity, uint64_t entityID);
	void removeEntity(uint64_t entityID);

	IEntity* getEntity(uint64_t entityID);

	uint64_t getPrimaryCameraID() { return _primaryCameraID; };

	const std::map<uint64_t, IEntity*>& getEntities();

	void setBoundingSphere(BoundingSphere* boundingSphere) { _boundingSphere = boundingSphere; }
	BoundingSphere* getBoundingSphere() { return _boundingSphere; }
};

