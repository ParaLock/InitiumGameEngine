#pragma once
#include "Particle.h"

class Texture;

struct ParticleBatch {
	int _numParticles;
	Texture* _particleTex;
	ParticleShape _shape;

	std::list<Particle*> _particleList;
};

class ParticleStream
{
private:
public:
	ParticleStream();
	~ParticleStream();

	bool isEmpty();

	ParticleBatch getNextBatch() { return ParticleBatch(); };
};

