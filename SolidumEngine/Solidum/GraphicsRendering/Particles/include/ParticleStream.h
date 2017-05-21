#pragma once
#include "../../../sysInclude.h"

class Texture;
class Particle;

struct ParticleBatch {

	Texture* _particleTex;

	int _currentInstanceBuffIndex = 0;

	std::shared_ptr<std::list<Particle*>> _particlesToRender;
};

class ParticleStream
{
private:
	std::list<std::shared_ptr<ParticleBatch>> _batches;
public:
	ParticleStream();
	~ParticleStream();

	void pushBatch(std::shared_ptr<ParticleBatch> batch) { _batches.push_back(batch); }

	bool isEmpty() { return _batches.empty(); };

	std::shared_ptr<ParticleBatch> getBatch() {

		if (!isEmpty()) {
			std::shared_ptr<ParticleBatch> batch = _batches.front();
			_batches.pop_front();
			
			return batch;
		}

		return nullptr;
	};
};

