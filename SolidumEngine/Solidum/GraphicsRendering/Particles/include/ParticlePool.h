#pragma once
#include "../../../ResourceFramework/include/ResourcePool.h"

#include "ParticleFactory.h"

#include "Particle.h"
class ParticleFactory;

class ParticlePool : public ResourcePool<Particle, PARTICLE_TYPE, ParticleFactory>
{
private:
public:
	ParticlePool(ParticleFactory* factory) { _factory = factory; }
	~ParticlePool() {};
};

