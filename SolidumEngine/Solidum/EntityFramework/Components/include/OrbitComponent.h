#pragma once

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "Component.h"

class IRenderDataPacket;

class OrbitComponent : public Component
{
private:
	Vector3f _pointToOrbit;

	float _orbitRadius;
	float _orbitSpeed;
	float _orbitAngle;

	void load() {};
	void unload() {};

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

public:
	OrbitComponent(Vector3f pointToOrbit, float radius, float speed, IEntity* entity);
	~OrbitComponent();

	struct InitData : public ResourceInitParams {
		InitData() {}

		

	};

	void onEvent(EVENT_PTR evt) {};

	void update(float delta);

	void AddRenderData(RenderDataGroup* collection) {};

protected:
};

