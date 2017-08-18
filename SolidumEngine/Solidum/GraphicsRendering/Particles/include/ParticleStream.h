#pragma once
#include "../../../sysInclude.h"

class Texture;
class Particle;
class IResource;

struct ParticleData {

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
};

struct ParticleBatch {

	IResource* _particleTex;

	int _currentInstanceBuffIndex = 0;

	std::list<ParticleData*> _particlesToRender;
};
