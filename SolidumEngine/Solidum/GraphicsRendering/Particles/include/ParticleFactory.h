#pragma once
#include "../../Particles/include/Particle.h"
#include "../../../ResourceFramework/include/ResourceFactory.h"

class ParticleFactory : public ResourceFactory<Particle, PARTICLE_TYPE>
{
public:
	ParticleFactory();
	~ParticleFactory();


	Particle* createObject(PARTICLE_TYPE type);
};

