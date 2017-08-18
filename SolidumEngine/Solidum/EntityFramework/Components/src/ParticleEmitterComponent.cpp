#include "../include/ParticleEmitterComponent.h"


ParticleEmitterComponent::ParticleEmitterComponent(
	float pps, float speed, float gravityComplient,
	float particleLifeLength, int maxParticles, int texNumRows,
	Texture* tex, BLEND_STATE state, CameraComponent* cam,
	IEntity* entity,
	ResourceCreator& resCreator) :
		_resourceCreator(resCreator)
{

	_particleLifeTime = particleLifeLength;
	_particleTex = tex;
	
	_blendState = state;

	_gravityComplient = gravityComplient;

	_texNumRows = texNumRows;

	_speed = speed;
	_pps = pps;

	_cam = cam;

	_parent = entity;

	_particleInstanceBuffer = resCreator.createResourceImmediate<GPUBuffer>(&GPUBuffer::InitData(maxParticles * sizeof(ParticleInstanceData), 
		BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE), std::to_string(getRandomNumber()) + "particle_instance_buffer",
		[](IResource*) {});

	_particleDataCPUBuffer = new ParticleInstanceData[maxParticles];

	std::string stlStr = std::to_string(getRandomNumber());

	_particleQuad = (mesh*)resCreator.createResourceImmediate<mesh>(&mesh::InitData(L"null", &resCreator), stlStr + "particle_quad", 
		[](IResource*) {}
		);

	float texWidth = tex->getWidth();
	float texHeight = tex->getHeight();

	float area = (texWidth * texHeight) / (texNumRows * texNumRows);

	float particleSideLength = sqrt(area);

	float left, right, top, bottom;

	left = (float)((particleSideLength / 2) * -1);
	right = left + (float)particleSideLength;
	top = (float)(particleSideLength / 2);
	bottom = top - (float)particleSideLength;

	_particleQuad->generatePlaneMesh(-0.52, 0.52, 0.52, -0.52, &resCreator);

	_maxParticles = maxParticles;

	_time.startTimer();

	_parent->getRenderObject()->addUniqueComponent(this);
}


ParticleEmitterComponent::~ParticleEmitterComponent()
{
}

Particle* ParticleEmitterComponent::emitParticle(Vector3f center)
{
	Particle* newParticle;

	float dirX = (float)getRandomNumber() * 2.0f - 1.0f;
	float dirZ = (float)getRandomNumber() * 2.0f - 1.0f;

	Vector3f velocity = Vector3f(dirX, 100, dirZ);

	velocity = Vector3f::normalize(velocity);

	velocity = velocity * _speed;

	newParticle = getDeadParticle(_resourceCreator);

	ParticleData* _particleData = newParticle->getData();

	_particleData->_isAlive = true;

	_particleData->_scale = 5.0f;

	_particleData->_elapsedTime = 0;
	_particleData->_lifeLength = _particleLifeTime;
	_particleData->_gravityEffect = _gravityComplient;
	_particleData->_velocity = velocity;

	_particleData->_texNumRows = _texNumRows;
	_particleData->_texOffset1 = 0;
	_particleData->_texOffset2 = 0;
	_particleData->_texBlend = 0;

	_particleData->_position = center;

	return newParticle;
}

bool ParticleEmitterComponent::updateParticle(Particle* particle, float delta)
{
	ParticleData* _particleData = particle->getData();

	_particleData->_velocity[1] += _gravityComplient * delta;
	Vector3f change = Vector3f(_particleData->_velocity);
	change = change * delta;
	_particleData->_position = change + _particleData->_position;

	updateParticleTextureState(particle);

	_particleData->_elapsedTime += delta;

	return _particleData->_elapsedTime < _particleLifeTime;
}

void ParticleEmitterComponent::updateParticleTextureState(Particle* particle)
{
	ParticleData* _particleData = particle->getData();

	float lifeFactor = _particleData->_elapsedTime / _particleData->_lifeLength;

	int stageCount = _particleData->_texNumRows * _particleData->_texNumRows;
	float atlasProgression = lifeFactor * stageCount;

	int index1 = floor(atlasProgression);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;

	_particleData->_texBlend = std::fmod(atlasProgression, 1);

	_particleData->_texOffset1 = calcTextureOffset(index1, _particleData->_texNumRows);
	_particleData->_texOffset2 = calcTextureOffset(index2, _particleData->_texNumRows);
}

Vector2f ParticleEmitterComponent::calcTextureOffset(int index, int rows)
{
	Vector2f offset;

	int column = fmod(index, rows);
	int row = index / rows;

	offset[0] = (float)column / rows;
	offset[1] = (float)row / rows;

	return offset;
}

Particle * ParticleEmitterComponent::getDeadParticle(ResourceCreator& resCreator)
{
	if (!_deadParticleList.empty()) {

		Particle* particle = _deadParticleList.back();
		
		_deadParticleList.pop_back();

		return particle;
	}

	Particle* newParticle = resCreator.createResourceImmediate<Particle>(&Particle::InitData(), "particle" + getRandomNumber(), [](IResource*) {});

	return newParticle;
}

void ParticleEmitterComponent::processParticles()
{
}

void ParticleEmitterComponent::update(float delta)
{
	//_particleBatchStore.clear();

	ParticleBatch batch;

	float t = (float)_time.getElapsedTimeSeconds();

	float particlesToCreate = _pps * t;

	int count = (int)floor(particlesToCreate);

	float partialParticle = std::fmod(particlesToCreate, 1.0f);

	for (int i = 0; i<count; i++) {

		_liveParticleList.push_back(emitParticle(_parent->getTransform()->getPos()));

	}
	if (getRandomNumber() < partialParticle) {

		_liveParticleList.push_back(emitParticle(_parent->getTransform()->getPos()));
	}

	std::list<Particle*>::iterator itr = _liveParticleList.begin();

	for (auto itr = _liveParticleList.begin(); itr != _liveParticleList.end();) {

		Particle* particle = *itr;

		if (!updateParticle(particle, t)) {

			Particle* deadParticle = *itr;

			itr = _liveParticleList.erase(itr);

			ParticleData* _data = deadParticle->getData();

			_data->_isAlive = false;
			_data->_elapsedTime = 0;

			_deadParticleList.push_back(deadParticle);
		}
		else {

			if (batch._particlesToRender.size() < _maxParticles) {

				ParticleData* _particleData = particle->getData();

				batch._particlesToRender.push_back(_particleData);
			}


			itr++;
		}
	}

	batch._particleTex = _particleTex;

	_particleBatchStore.push_back(batch);
	
	_time.reset();
}

void ParticleEmitterComponent::AddRenderData(RenderDataGroup * collection)
{
	RenderPassPacket_ParticleEmitterData data;
	RenderDataAttributes attributes;

	data._maxParticles = _maxParticles;

	data._particleInstanceBuffer = _particleInstanceBuffer;
	data._particleDataCPUBuffer = _particleDataCPUBuffer;

	data._particleSteam = &_particleBatchStore;

	data._indexBuffer = _particleQuad->getIndexBuff();
	data._vertexBuffer = _particleQuad->getVertexBuff();
	data._numIndices = _particleQuad->numIndices;

	data._translationMatrix = _parent->getTransform()->getGlobalTransform();

	collection->addRenderData<RenderPassPacket_ParticleEmitterData>(&data, RENDER_DATA_TYPE::RENDER_PARTICLE_EMITTER_DATA, &attributes);
}

