#pragma once
#include "../../../sysInclude.h"
#include "../../../ResourceFramework/include/IResource.h"

class Particle : public IResource
{
private:
	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	void load(std::shared_ptr<IResourceBuilder> builder) { isLoaded = true; };
	void unload() { 

		isLoaded = false; 
		
		_elapsedTime = 0;
	};

	PARTICLE_TYPE _type;
public:
	Particle();
	~Particle();

	PARTICLE_TYPE getType() { return _type; }

	Vector2f _texOffset1;
	Vector2f _texOffset2;

	Vector3f _distanceFromCamera;

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


