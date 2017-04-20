#include "../include/ParticleRenderNode.h"



ParticleRenderNode::ParticleRenderNode()
{
}


ParticleRenderNode::~ParticleRenderNode()
{
}

void ParticleRenderNode::load(std::shared_ptr<IResourceBuilder> builder) {

	InitData* realBuilder = static_cast<InitData*>(builder.get());

	std::shared_ptr<ParticleEmitterRenderNodeParams> params = std::make_shared<ParticleEmitterRenderNodeParams>();

	_renderParams.setCustomRenderParams(params);

	_shader = realBuilder->_shader;

	params->_particleRenderShader = realBuilder->_shader;
	params->_particles = realBuilder->_particles;

	std::vector<ShaderInputLayoutElement*>* inputLayout = _shader->getPipeline()->getInputLayout()->getElementList();

	inputLayout->operator[](inputLayout->size())->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;

	_shader->getPipeline()->getInputLayout()->generateInputLayout();

	params->_particleInstanceBuffer = ResourceManagerPool::getInstance()->getResourceManager("GPUBufferManager")->createResource(std::make_shared<GPUBuffer::InitData>
		(realBuilder->_maxParticles * sizeof(ParticleInstanceData), BUFFER_TYPE::INSTANCE_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE), 
			std::to_string(getRandomNumber()) + "particle_instance_buffer", false)->getCore<GPUBuffer>();


	isLoaded = true;

}

void ParticleRenderNode::unload() {
	isLoaded = false;
}

bool ParticleRenderNode::isRenderViable()
{
	ParticleEmitterRenderNodeParams* params = (ParticleEmitterRenderNodeParams*)_renderParams.getCustomRenderParams().get();

	if (params->_particleRenderShader == nullptr)
		return false;
	if (params->_particles->isEmpty())
		return false;

	return true;
}

void ParticleRenderNode::render() {

	GraphicsCommandList* commandList = new GraphicsCommandList();

	ParticleEmitterRenderNodeParams* params = (ParticleEmitterRenderNodeParams*)_renderParams.getCustomRenderParams().get();

	size_t currentInstanceBuffOffset = 0;

	mesh* quad = nullptr;

	if (isRenderViable()) {

		while (!params->_particles->isEmpty()) {
			
			ParticleBatch batch = params->_particles->getNextBatch();

			if (params->_particleMeshCache.find(batch._shape) == params->_particleMeshCache.end()) {

				std::string stlStr = std::to_string(getRandomNumber());

				quad = (mesh*)ResourceManagerPool::getInstance()->getResourceManager("meshManager")->
					createResource(std::make_shared<mesh::InitData>(L"null", nullptr), stlStr + "particle_quad", false);

				quad->generatePlaneMesh(batch._shape.top, batch._shape.bottom,
					batch._shape.left, batch._shape.right);

				params->_particleMeshCache.insert({ batch._shape, quad });
			}

			quad = params->_particleMeshCache.at(batch._shape);


			for each(Particle* particle in batch._particleList) {

				if (currentInstanceBuffOffset != params->_particleInstanceBuffer->getSize()) {

					ParticleInstanceData particleData;

					particleData._position = particle->_position;

					params->_particleInstanceBuffer->Write(&particleData, sizeof(ParticleInstanceData), currentInstanceBuffOffset);

					currentInstanceBuffOffset += sizeof(ParticleInstanceData);
				}
			}

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {quad->getVertexBuff(), params->_particleInstanceBuffer},
				 std::vector<UINT> {0,0},
				 std::vector<UINT> {_shader->getPipeline()->getInputLayout()->getDataStride()}),
				
				 GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER);
		}
	}
}