#include "../include/ParticleFactory.h"



ParticleFactory::ParticleFactory()
{
}


ParticleFactory::~ParticleFactory()
{
}

Particle * ParticleFactory::createObject(PARTICLE_TYPE type)
{
	Particle* particle = nullptr;

	switch (type) {
	case PARTICLE_TYPE::STANDARD:
		particle = new Particle();
		break;
	}

	return particle;
}
