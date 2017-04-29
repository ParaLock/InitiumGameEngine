#pragma once
#include "../../../EventFramework/include/IEvent.h"
#include "../../../EventFramework/include/InputEvent.h"

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "../../../GraphicsRendering/Particles/include/Particle.h"
#include "../../../GraphicsRendering/Particles/include/ParticleStream.h"

#include "../../../GraphicsRendering/RenderNode/include/RenderNodePool.h"

#include "CameraComponent.h"

#include "Component.h"

class ParticleEmitterComponent : public Component
{
private:

	std::list<Particle*> _deadParticleList;
	std::list<Particle*> _liveParticleList;

	Texture* _particleTex;

	CameraComponent* _cam;

	ParticleStream* _stream;

	mesh* _particleQuad;

	BLEND_STATE _blendState;

	float _particleLifeTime;
	float _gravityComplient;
	float _pps;
	float _speed;

	int _maxParticles;
	int _texNumRows;

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { isLoaded = false; };

	HRTimer _time;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void onEvent(EVENT_PTR evt) {};

	Particle* emitParticle(Vector3f center);

	bool updateParticle(Particle* particle, float delta);
	void updateParticleTextureState(Particle* particle);

	Vector2f calcTextureOffset(int index, int rows);

	Particle* getDeadParticle();

public:
	ParticleEmitterComponent(
		float pps, float speed, float gravityComplient, 
		float particleLifeLength, int maxParticles, int texNumRows, Shader* shader,
		Texture* tex, BLEND_STATE state, CameraComponent* cam,
		IEntity* entity);

	~ParticleEmitterComponent();

	void update(float delta);
};

