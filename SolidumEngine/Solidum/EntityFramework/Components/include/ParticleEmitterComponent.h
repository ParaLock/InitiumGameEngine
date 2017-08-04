#pragma once

#include "../../../GraphicsRendering/Transform/include/Transform.h"

#include "../../../EngineUtils/include/Vector2.h"
#include "../../../EngineUtils/include/Vector3.h"

#include "../../../GraphicsRendering/Particles/include/Particle.h"
#include "../../../GraphicsRendering/Particles/include/ParticleStream.h"

#include "../../../TaskFramework/include/TaskTree.h"

#include "../../../GraphicsRendering/RenderDataProtocal/include/RenderDataGroup.h"

#include "../../../GraphicsRendering/Mesh/include/mesh.h"

#include "../../../GraphicsRendering/Textures/include/Texture.h"

#include "CameraComponent.h"

#include "Component.h"

struct RenderPassPacket_ParticleEmitterData {
	int _maxParticles = 0;

	int _numIndices;

	IResource* _indexBuffer;
	IResource* _vertexBuffer;

	IResource* _particleInstanceBuffer;

	ParticleStream* _particleSteam;
	ParticleInstanceData* _particleDataCPUBuffer;

	Matrix4f _translationMatrix;
};

class ParticleEmitterComponent : public Component
{
private:

	std::list<Particle*> _deadParticleList;
	std::list<Particle*> _liveParticleList;

	IResource* _particleInstanceBuffer;

	ParticleInstanceData* _particleDataCPUBuffer;

	Texture* _particleTex;

	CameraComponent* _cam;

	ParticleStream* _stream;

	mesh* _particleQuad;

	BLEND_STATE _blendState;

	ResourceCreator& _resourceCreator;

	float _particleLifeTime;
	float _gravityComplient;
	float _pps;
	float _speed;

	int _maxParticles;
	int _texNumRows;

	void load() { };
	void unload() { };

	HRTimer _time;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void onEvent(EVENT_PTR evt) {};

	Particle* emitParticle(Vector3f center);

	bool updateParticle(Particle* particle, float delta);
	void updateParticleTextureState(Particle* particle);

	Vector2f calcTextureOffset(int index, int rows);

	Particle* getDeadParticle(ResourceCreator& resCreator);

	void processParticles();

public:
	ParticleEmitterComponent(
		float pps, float speed, float gravityComplient, 
		float particleLifeLength, int maxParticles, int texNumRows,
		Texture* tex, BLEND_STATE state, CameraComponent* cam,
		IEntity* entity,
		ResourceCreator& resCreator);

	~ParticleEmitterComponent();

	struct InitData : public ResourceInitParams {
		InitData() {}

		
	};

	void update(float delta);

	void AddRenderData(RenderDataGroup* collection);

protected:
};

