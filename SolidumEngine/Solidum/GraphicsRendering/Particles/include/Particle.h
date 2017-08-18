#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/Resource.h"

#include "ParticleStream.h"

class GenericFactory;

class ResourcePool;

class Particle : public Resource<Particle, GenericFactory, ResourcePool>
{
private:

	ParticleData _data;

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {};
	void unload() { _data._elapsedTime = 0;};

public:
	Particle();
	~Particle();

	struct InitData : public ResourceInitParams {
		InitData() {}

		
	};

	ParticleData* getData();

protected:
};


