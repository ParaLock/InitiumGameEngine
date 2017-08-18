#include "../include/Particle.h"



Particle::Particle()
{
}


Particle::~Particle()
{
}

ParticleData * Particle::getData()
{
	return &_data;
}
