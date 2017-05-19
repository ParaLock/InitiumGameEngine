#include "../include/ParticleRenderer.h"



ParticleRenderer::ParticleRenderer()
{

	_type = RENDERER_TYPE::PARTICLE_RENDERER;
}


ParticleRenderer::~ParticleRenderer()
{
}

Matrix4f ParticleRenderer::createParticleMVMatrix(Vector3f pos, float rotation, float scale, 
	const Matrix4f& matView, const Matrix4f matWorld)
{
	Matrix4f viewMatrix = matView;
	Matrix4f world = matWorld;

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

void ParticleRenderer::DeferredInit()
{
	_particleRenderingShader = _shaders.at("particle_shader");

	std::vector<ShaderInputLayoutElement*>* inputLayout = _particleRenderingShader->getInputLayout()->getElementList();

	//Definition of INSTANCE_DATA Buffer format

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

	_particleRenderingShader->getInputLayout()->generateInputLayout();

}

void ParticleRenderer::gatherAndPrepareNodes(IRenderNodeTree * tree)
{
	_particleRenderNodes = tree->queryNodesByType(RENDER_NODE_TYPE::PARTICLE_EMITTER_RENDER_NODE);
}

void ParticleRenderer::processNodes(GraphicsCommandList * commandList)
{
	for each(RenderNode* particleNode in _particleRenderNodes) {

		RenderParams* params = particleNode->getRenderParams();

		Matrix4f worldMatrix = params->getGlobalParam_GlobalRenderingCamera()->getWorldMatrix();
		Matrix4f viewMatrix = params->getGlobalParam_GlobalRenderingCamera()->getViewMatrix();

		ParticleEmitterRenderNodeParams* particleParams = (ParticleEmitterRenderNodeParams*)params->getCustomRenderParams().get();

		while (!particleParams->_particles->isEmpty()) {

			ParticleBatch batch = particleParams->_particles->getBatch();

			int i = 0;

			for each(Particle* particle in batch._particlesToRender) {

				ParticleInstanceData particleData;

				particleData._mvMatrix = Matrix4f::transpose(createParticleMVMatrix(particle->_position, particle->_rotation, particle->_scale, viewMatrix, worldMatrix));

				particleData._texOffset1 = particle->_texOffset1;
				particleData._texOffset2 = particle->_texOffset2;

				particleData._texCoordInfo[0] = particle->_texNumRows;
				particleData._texCoordInfo[1] = particle->_texBlend;

				particleParams->_particleDataCPUBuffer[i] = particleData;

				i++;
			}

			particleParams->_particleInstanceBuffer->Write(particleParams->_particleDataCPUBuffer, sizeof(ParticleInstanceData) * particleParams->_maxParticles, 0);

			_particleRenderingShader->updateModelUniforms(params->getPerNodeParam_Transform());

			commandList->createCommand(std::make_shared<ShaderUpdateCameraUniformsCommand::InitData>
				(params->getGlobalParam_GlobalRenderingCamera(), _particleRenderingShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_CAMERA_UNIFORMS);

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {params->getPerNodeParam_Mesh()->getIndexBuff()},
					std::vector<UINT> {0},
					std::vector<UINT> {0}),

				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER
				);

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {params->getPerNodeParam_Mesh()->getVertexBuff(), particleParams->_particleInstanceBuffer},
					std::vector<UINT> {0, 0},
					std::vector<UINT> {sizeof(LIGHT_VERTEX), sizeof(ParticleInstanceData)}),

				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_particleRenderingShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			_pipelineState->shaderSetVertexInputLayout(_particleRenderingShader->getInputLayout());

			_pipelineState->setBlendState(params->getPerNodeParam_BlendState());
			_pipelineState->setDepthTestState(DEPTH_TEST_STATE::FULL_DISABLE);
			_pipelineState->setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _particleRenderingShader->getConstantBuffers();

			for (auto itr = constantBuffs.begin(); itr != constantBuffs.end(); itr++) {

				singleStructs.insert(itr->second);
			}

			for (auto itr = singleStructs.begin(); itr != singleStructs.end(); itr++) {

				std::pair<SHADER_TYPE, DynamicStruct*> data = *itr;

				DynamicStruct* buff = data.second;

				_pipelineState->attachResource(buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
			}

			_ioInterface->assignHookResourceByName("particle_texture", batch._particleTex);

			rebuildPSO();

			_pipelineState->applyState(commandList);

			_particleRenderingShader->execute(commandList);

			_pipelineState->reset();

			commandList->createCommand(std::make_shared<PipelineDrawInstancedCommand::InitData>(params->getPerNodeParam_Mesh()->numIndices, batch._particlesToRender.size()),
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INSTANCED);

			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
	}
}
