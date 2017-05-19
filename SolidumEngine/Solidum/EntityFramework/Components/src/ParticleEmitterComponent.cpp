#include "../include/ParticleEmitterComponent.h"


ParticleEmitterComponent::ParticleEmitterComponent(
	float pps, float speed, float gravityComplient,
	float particleLifeLength, int maxParticles, int texNumRows,
	Texture* tex, BLEND_STATE state, CameraComponent* cam,
	IEntity* entity)
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

	_type = COMPONENT_TYPE::PARTICLE_COMPONENT;

	_stream = new ParticleStream();

	IGraphicsCore* gCore = IGraphicsCore::getInstance();
	RenderNodePool* renderNodePool = gCore->getRenderNodePool();

	RenderNode* node = renderNodePool->getResource(RENDER_NODE_TYPE::PARTICLE_EMITTER_RENDER_NODE);

	_parent->getRenderObject()->addGenericRenderNode(node, 0);

	node->load(std::make_shared<ParticleRenderNode::InitData>(_stream, 4000));

	std::string stlStr = std::to_string(getRandomNumber());

	_particleQuad = (mesh*)ResourceManagerPool::getInstance()->getResourceManager("meshManager")->
		createResource(std::make_shared<mesh::InitData>(L"null", nullptr), stlStr + "particle_quad", false);

	float texWidth = tex->getWidth();
	float texHeight = tex->getHeight();

	float area = (texWidth * texHeight) / (texNumRows * texNumRows);

	float particleSideLength = sqrt(area);

	float left, right, top, bottom;

	left = (float)((particleSideLength / 2) * -1);
	right = left + (float)particleSideLength;
	top = (float)(particleSideLength / 2);
	bottom = top - (float)particleSideLength;

	_particleQuad->generatePlaneMesh(-0.52, 0.52, 0.52, -0.52);

	node->getRenderParams()->setPerNodeParam_Mesh(_particleQuad);
	node->getRenderParams()->setPerNodeParam_Transform(_parent->getTransform());
	node->getRenderParams()->setPerNodeParam_BlendState(_blendState);

	ParticlePool* particlePool = IGraphicsCore::getInstance()->getParticlePool();
	
	_maxParticles = maxParticles;

	_time.startTimer();
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

	newParticle = getDeadParticle();

	newParticle->_isAlive = true;

	newParticle->_scale = 5.0f;

	newParticle->_elapsedTime = 0;
	newParticle->_lifeLength = _particleLifeTime;
	newParticle->_gravityEffect = _gravityComplient;
	newParticle->_velocity = velocity;

	newParticle->_texNumRows = _texNumRows;
	newParticle->_texOffset1 = 0;
	newParticle->_texOffset2 = 0;
	newParticle->_texBlend = 0;

	newParticle->_position = center;

	return newParticle;
}

bool ParticleEmitterComponent::updateParticle(Particle* particle, float delta)
{
	particle->_velocity[1] += _gravityComplient * delta;
	Vector3f change = Vector3f(particle->_velocity);
	change = change * delta;
	particle->_position = change + particle->_position;

	updateParticleTextureState(particle);

	particle->_elapsedTime += delta;

	//particle->_distanceFromCamera = pow(Vector3f::length((_cam->getPos - particle->_position)), 2);

	return particle->_elapsedTime < _particleLifeTime;
}

void ParticleEmitterComponent::updateParticleTextureState(Particle* particle)
{
	float lifeFactor = particle->_elapsedTime / particle->_lifeLength;

	int stageCount = particle->_texNumRows * particle->_texNumRows;
	float atlasProgression = lifeFactor * stageCount;

	int index1 = floor(atlasProgression);
	int index2 = index1 < stageCount - 1 ? index1 + 1 : index1;

	particle->_texBlend = std::fmod(atlasProgression, 1);

	particle->_texOffset1 = calcTextureOffset(index1, particle->_texNumRows);
	particle->_texOffset2 = calcTextureOffset(index2, particle->_texNumRows);

	int debug = -1;
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

Particle * ParticleEmitterComponent::getDeadParticle()
{
	ParticlePool* particlePool = IGraphicsCore::getInstance()->getParticlePool();

	if (!_deadParticleList.empty()) {
		Particle* particle = _deadParticleList.back();
		
		_deadParticleList.pop_back();

		return particle;
	}

	return particlePool->getResource(PARTICLE_TYPE::STANDARD);
}

void ParticleEmitterComponent::update(float delta)
{
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

			deadParticle->_isAlive = false;
			deadParticle->_elapsedTime = 0;

			_deadParticleList.push_back(deadParticle);
		}
		else {

			if (batch._particlesToRender.size() < _maxParticles)
				batch._particlesToRender.push_back(particle);

			itr++;
		}
	}

	//Sort batch._particlesToRender

	batch._particleTex = _particleTex;

	_stream->pushBatch(batch);
	
	_time.reset();
}
