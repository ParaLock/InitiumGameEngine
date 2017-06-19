#pragma once

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "Component.h"

class RenderDataPacket;

class OrbitComponent : public Component
{
private:
	Vector3f _pointToOrbit;

	float _orbitRadius;
	float _orbitSpeed;
	float _orbitAngle;

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

public:
	OrbitComponent(Vector3f pointToOrbit, float radius, float speed, IEntity* entity);
	~OrbitComponent();

	void onEvent(EVENT_PTR evt) {};

	void update(float delta);

	void AddRenderData(RenderDataGroup* collection) {};
};

