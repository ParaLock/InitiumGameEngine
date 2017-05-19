#include "../include/ParticleRenderNode.h"



ParticleRenderNode::ParticleRenderNode()
{
	_type = RENDER_NODE_TYPE::PARTICLE_EMITTER_RENDER_NODE;
}


ParticleRenderNode::~ParticleRenderNode()
{
}

void ParticleRenderNode::load(std::shared_ptr<IResourceBuilder> builder) {

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	std::shared_ptr<ParticleEmitterRenderNodeParams> params = std::make_shared<ParticleEmitterRenderNodeParams>();

	_renderParams.setCustomRenderParams(params);

	params->_particles = realBuilder->_particles;

	params->_maxParticles = realBuilder->_maxParticles;


	params->_particleInstanceBuffer = ResourceManagerPool::getInstance()->getResourceManager("GPUBufferManager")->createResource(std::make_shared<GPUBuffer::InitData>
		(realBuilder->_maxParticles * sizeof(ParticleInstanceData), BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE), 
			std::to_string(getRandomNumber()) + "particle_instance_buffer", false)->getCore<GPUBuffer>();

	params->_particleDataCPUBuffer = new ParticleInstanceData[params->_maxParticles];

	isLoaded = true;

}

void ParticleRenderNode::unload() {

	_parent = nullptr;
	_child = nullptr;

	isLoaded = false;
}

bool ParticleRenderNode::isRenderViable()
{
	ParticleEmitterRenderNodeParams* params = (ParticleEmitterRenderNodeParams*)_renderParams.getCustomRenderParams().get();

	if (params->_particles->isEmpty())
		return false;

	return true;
}



void ParticleRenderNode::render() {

}