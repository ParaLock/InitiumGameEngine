#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/Resource.h"

#include "ParticleStream.h"

class GenericFactory;

class ResourcePool;

class Particle : public Resource<Particle, GenericFactory, ResourcePool>
{
private:
	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load() {};
	void unload() { _elapsedTime = 0;};

public:
	Particle();
	~Particle();

	struct InitData : public ResourceInitParams {
		InitData() {}

		
	};


	static const unsigned int TYPE = 0;

	int _batchIndex = 0;

	Vector2f _texOffset1;
	Vector2f _texOffset2;

	float _distance;

	int _texNumRows;

	float _texBlend;

	float _gravityEffect = 0;
	float _rotation = 0;
	float _scale = 0;

	float _elapsedTime = 0;
	float _lifeLength = 0;

	bool _isAlive = false;

	Vector3f _velocity;
	Vector3f _position;

protected:
};


