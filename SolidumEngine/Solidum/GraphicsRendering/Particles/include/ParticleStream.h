#pragma once
#include "Particle.h"

class Texture;

struct ParticleBatch {
	Texture* _particleTex;

	std::list<Particle*> _particlesToRender;
};

class ParticleStream
{
private:
	std::list<ParticleBatch> _batches;
public:
	ParticleStream();
	~ParticleStream();

	void pushBatch(ParticleBatch batch) { _batches.push_back(batch); }

	bool isEmpty() { return _batches.empty(); };

	ParticleBatch getBatch() {

		if (!isEmpty()) {
			ParticleBatch batch = _batches.front();
			_batches.pop_front();
			
			return batch;
		}

		return ParticleBatch();
	};
};

