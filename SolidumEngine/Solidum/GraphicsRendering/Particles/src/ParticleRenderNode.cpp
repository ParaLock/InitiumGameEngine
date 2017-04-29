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

	params->_maxParticles = realBuilder->_maxParticles;

	std::vector<ShaderInputLayoutElement*>* inputLayout = _shader->getPipeline()->getInputLayout()->getElementList();
	
	//OTHER
	inputLayout->operator[](inputLayout->size() - 5)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;
	inputLayout->operator[](inputLayout->size() - 5)->_hardCodedIndex = true;
	inputLayout->operator[](inputLayout->size() - 5)->_index = 0;

	inputLayout->operator[](inputLayout->size() - 6)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;
	inputLayout->operator[](inputLayout->size() - 6)->_hardCodedIndex = true;
	inputLayout->operator[](inputLayout->size() - 6)->_index = 0;

	inputLayout->operator[](inputLayout->size() - 7)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;
	inputLayout->operator[](inputLayout->size() - 7)->_hardCodedIndex = true;
	inputLayout->operator[](inputLayout->size() - 7)->_index = 0;

	//MATRIX
	inputLayout->operator[](inputLayout->size() - 1)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;

	inputLayout->operator[](inputLayout->size() - 2)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;

	inputLayout->operator[](inputLayout->size() - 3)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;

	inputLayout->operator[](inputLayout->size() - 4)->_class = INPUT_LAYOUT_ELEMENT_CLASS::PER_INSTANCE_DATA;

	_shader->getPipeline()->getInputLayout()->generateInputLayout();

	params->_particleInstanceBuffer = ResourceManagerPool::getInstance()->getResourceManager("GPUBufferManager")->createResource(std::make_shared<GPUBuffer::InitData>
		(realBuilder->_maxParticles * sizeof(ParticleInstanceData), BUFFER_TYPE::VERTEX_BUFF, BUFFER_CPU_ACCESS::CPU_ACCESS_WRITE), 
			std::to_string(getRandomNumber()) + "particle_instance_buffer", false)->getCore<GPUBuffer>();

	_type = RENDER_NODE_TYPE::PARTICLE_EMITTER_RENDER_NODE;

	_particleDataCPUBuffer = new ParticleInstanceData[params->_maxParticles];

	isLoaded = true;

}

void ParticleRenderNode::unload() {

	delete _particleDataCPUBuffer;

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

Matrix4f ParticleRenderNode::createParticleMVMatrix(Vector3f pos, float rotation, float scale)
{
	Matrix4f viewMatrix = _renderParams.getGlobalParam_GlobalRenderingCamera()->getViewMatrix();
	Matrix4f projection = _renderParams.getGlobalParam_GlobalRenderingCamera()->getProjectionMatrix();
	Matrix4f world = _renderParams.getGlobalParam_GlobalRenderingCamera()->getWorldMatrix();

	Matrix4f modelMatrix = Matrix4f::get_identity();

	Matrix4f translationMatrix = Matrix4f::get_identity();
	Matrix4f rotationMatrix = Matrix4f::get_identity();
	Matrix4f scaleMatrix = Matrix4f::get_identity();

	translationMatrix = Matrix4f::get_translation(Vector3f(pos));

	float radRot = DEG_TO_RAD * rotation;

	rotationMatrix = Matrix4f::rotate(Vector3f(radRot, radRot, radRot), Vector3f(0, 0, 1), rotationMatrix);
	scaleMatrix = Matrix4f::get_scale(Vector3f(scale, scale, scale));

	modelMatrix = world * translationMatrix * scaleMatrix;

	modelMatrix[0][0] = viewMatrix[0][0];
	modelMatrix[0][1] = viewMatrix[1][0];
	modelMatrix[0][2] = viewMatrix[2][0];
	modelMatrix[1][0] = viewMatrix[0][1];
	modelMatrix[1][1] = viewMatrix[1][1];
	modelMatrix[1][2] = viewMatrix[2][1];
	modelMatrix[2][0] = viewMatrix[0][2];
	modelMatrix[2][1] = viewMatrix[1][2];
	modelMatrix[2][2] = viewMatrix[2][2];

	modelMatrix = modelMatrix * scaleMatrix;

	return viewMatrix * modelMatrix;
}

void ParticleRenderNode::render() {

	GraphicsCommandList* commandList = new GraphicsCommandList();

	ParticleEmitterRenderNodeParams* params = (ParticleEmitterRenderNodeParams*)_renderParams.getCustomRenderParams().get();

	if (isRenderViable()) {

		while (!params->_particles->isEmpty()) {
			
			ParticleBatch batch = params->_particles->getBatch();

			int i = 0;

			for each(Particle* particle in batch._particlesToRender) {

				ParticleInstanceData particleData;

				particleData._mvMatrix = Matrix4f::transpose(createParticleMVMatrix(particle->_position, particle->_rotation, particle->_scale));

				particleData._texOffset1 = particle->_texOffset1;
				particleData._texOffset2 = particle->_texOffset2;

				particleData._texCoordInfo[0] = particle->_texNumRows;
				particleData._texCoordInfo[1] = particle->_texBlend;

				_particleDataCPUBuffer[i] = particleData;

				i++;
			}

			params->_particleInstanceBuffer->Write(_particleDataCPUBuffer, sizeof(ParticleInstanceData) * params->_maxParticles, 0);

			_shader->updateModelUniforms(_renderParams.getPerNodeParam_Transform());

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(_renderParams.getGlobalParam_GlobalRenderingCamera(), _shader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {_renderParams.getPerNodeParam_Mesh()->getIndexBuff()},
					std::vector<UINT> {0},
					std::vector<UINT> {0}),

					GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER
				);

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {_renderParams.getPerNodeParam_Mesh()->getVertexBuff(), params->_particleInstanceBuffer},
					std::vector<UINT> {0, 0},
					std::vector<UINT> {sizeof(LIGHT_VERTEX), sizeof(ParticleInstanceData)}),

				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_shader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_shader->getPipeline()->setBlendState(_renderParams.getPerNodeParam_BlendState());
			_shader->getPipeline()->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			_shader->getPipeline()->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			_shader->setModelTexture(batch._particleTex);

			_shader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawInstancedCommand::InitData>(_renderParams.getPerNodeParam_Mesh()->numIndices, batch._particlesToRender.size()),
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INSTANCED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}

	}

	_renderParams.setPerNodeParam_isVisible(false);

	GCLQManager::getInstance()->getPrimaryCommandQueue()->queueCommandList(commandList);
}