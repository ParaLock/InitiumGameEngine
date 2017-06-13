#pragma once
#include "../../Solidum/sysInclude.h"
#include "../../Solidum/GraphicsRendering/RenderPass/include/RenderPassWrapper.h"

#include "../../Solidum/EntityFramework/Components/include/ParticleEmitterComponent.h"

#include "../../Solidum/GraphicsRendering/Particles/include/InsertionSort.h"

static void reg_render_pass__particleEmitter(std::function<void(std::shared_ptr<RenderPassWrapper>)> regCallback) {
	std::shared_ptr<RenderPassWrapper> wrapper = std::make_shared<RenderPassWrapper>();

	wrapper->load(std::make_shared<RenderPassWrapper::InitData>("./res/RenderPassDescriptors/ParticleRenderPass.txt"));

	IShader* _particleRenderingShader = wrapper->getShader("particle_shader");

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


	wrapper->setRenderPass
		(
			[=](GraphicsCommandList* commandList, RenderDataGroup* collection, RenderPassWrapper* wrapper)
	{

		IShader* _particleRenderingShader = wrapper->getShader("particle_shader");

		auto createParticleMVMatrix = [](Vector3f pos, float rotation, float scale,
			const Matrix4f& matView, const Matrix4f matWorld) {

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

		};

		struct SceneParticles {

			std::vector<std::tuple<std::shared_ptr<ParticleBatch>, RenderPassPacket_ParticleEmitterData*>> _particleListByBatchIndex;

			std::vector<Particle*> _sortedParticleList;
		};

		SceneParticles sceneParticles;

		std::list<std::shared_ptr<RenderDataPacket>>& renderData = collection->getRenderDataByType(RENDER_DATA_TYPE::RENDER_PARTICLE_EMITTER_DATA);

		int currentBatchCount = 0;


		for each(std::shared_ptr<RenderDataPacket> particleEmitter in renderData) {

			RenderPassPacket_ParticleEmitterData* particleEmitterData = particleEmitter->getData<RenderPassPacket_ParticleEmitterData>();
			RenderData_GlobalData* _globalData = collection->getGlobalData();

			//PARTICLE REMOVAL FROM BATCH
			while (!particleEmitterData->_particleSteam->isEmpty()) {

				std::shared_ptr<ParticleBatch> batch = particleEmitterData->_particleSteam->getBatch();

				if (batch->_particlesToRender->size() < 2) {

					continue;
				}

				sceneParticles._particleListByBatchIndex.push_back(std::make_tuple(batch, particleEmitterData));

				for each(Particle* particle in *batch->_particlesToRender) {

					sceneParticles._sortedParticleList.push_back(particle);

					particle->_batchIndex = currentBatchCount;

					particle->_distance = Vector3f::distance_between(particle->_position, _globalData->global_cam._eyePosition);
				}

				batch->_particlesToRender->clear();

				currentBatchCount++;
			}
		}

		//PARTICLE SORTING
		InsertionSort sort;

		sort.particleSelectionSort(&sceneParticles._sortedParticleList);

		//PARTICLE REGROUPING WITH BATCH
		for each(Particle* particle in sceneParticles._sortedParticleList) {

			ParticleInstanceData particleData;

			std::cout << particle->_distance << std::endl;

			int batchIndex = particle->_batchIndex;

			RenderPassPacket_ParticleEmitterData* particleEmitter = std::get<1>(sceneParticles._particleListByBatchIndex.at(batchIndex));

			std::shared_ptr<ParticleBatch> batch = std::get<0>(sceneParticles._particleListByBatchIndex.at(batchIndex));

			Matrix4f worldMatrix = collection->getGlobalData()->global_cam._worldMatrix;
			Matrix4f viewMatrix = collection->getGlobalData()->global_cam._viewMatrix;

			particleData._mvMatrix = Matrix4f::transpose(createParticleMVMatrix(particle->_position, particle->_rotation, particle->_scale, viewMatrix, worldMatrix));

			particleData._texOffset1 = particle->_texOffset1;
			particleData._texOffset2 = particle->_texOffset2;

			particleData._texCoordInfo[0] = particle->_texNumRows;
			particleData._texCoordInfo[1] = particle->_texBlend;

			particleEmitter->_particleDataCPUBuffer[batch->_currentInstanceBuffIndex] = particleData;

			batch->_particlesToRender->push_back(particle);

			batch->_currentInstanceBuffIndex++;
		}


		//ORDER BATCHES BY DISTANCE TO CAMERA
		sort.particleBatchSelectionSort(&sceneParticles._particleListByBatchIndex);

		//PARTICLE RENDERING
		for each(std::tuple<std::shared_ptr<ParticleBatch>, RenderPassPacket_ParticleEmitterData*> particleDataTuple
			in sceneParticles._particleListByBatchIndex)
		{

			GPUPipeline pipelineState;

			RenderPassPacket_ParticleEmitterData* particleRenderData = std::get<1>(particleDataTuple);

			RenderData_GlobalData* globalData = collection->getGlobalData();

			std::shared_ptr<ShaderUniformGroup> globalDataUniforms = std::make_shared<ShaderUniformGroup>();

			globalDataUniforms->addUniform<Matrix4f>(Matrix4f::transpose(globalData->global_cam._projectionMatrix), "cbuff_projectionMatrix");

			std::shared_ptr<ParticleBatch> batch = std::get<0>(particleDataTuple);

			GPUBuffer* _particleInstanceBufferCasted = (GPUBuffer*)particleRenderData->_particleInstanceBuffer;

			_particleInstanceBufferCasted->Write(particleRenderData->_particleDataCPUBuffer, sizeof(ParticleInstanceData) * particleRenderData->_maxParticles, 0);

			commandList->createCommand(std::make_shared<ShaderUpdateUniformCommand::InitData>
				(globalDataUniforms, _particleRenderingShader), GRAPHICS_COMMAND_TYPE::SHADER_UPDATE_UNIFORM);
		
			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {(GPUBuffer*)particleRenderData->_indexBuffer},
					std::vector<UINT> {0},
					std::vector<UINT> {0}),

				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER
				);

			commandList->createCommand(std::make_shared<PipelineBufferBindCommand::InitData>
				(std::vector<GPUBuffer*> {(GPUBuffer*)particleRenderData->_vertexBuffer, (GPUBuffer*)particleRenderData->_particleInstanceBuffer},
					std::vector<UINT> {0, 0},
					std::vector<UINT> {sizeof(LIGHT_VERTEX), sizeof(ParticleInstanceData)}),

				GRAPHICS_COMMAND_TYPE::PIPELINE_BIND_VERTEX_BUFFER);

			commandList->createCommand(std::make_shared<ShaderSyncUniforms::InitData>(_particleRenderingShader), GRAPHICS_COMMAND_TYPE::SHADER_SYNC_UNIFORMS);

			pipelineState.shaderSetVertexInputLayout(_particleRenderingShader->getInputLayout());

			pipelineState.setBlendState(BLEND_STATE::ADDITIVE_BLENDING);
			pipelineState.setDepthTestState(DEPTH_TEST_STATE::LESS_EQUAL);
			pipelineState.setRasterState(RASTER_STATE::DISABLE_TRIANGLE_CULL);

			std::set<std::pair<SHADER_TYPE, DynamicStruct*>> singleStructs;

			auto& constantBuffs = _particleRenderingShader->getConstantBuffers();

			for (auto itr = constantBuffs.begin(); itr != constantBuffs.end(); itr++) {

				singleStructs.insert(itr->second);
			}

			for (auto itr = singleStructs.begin(); itr != singleStructs.end(); itr++) {

				std::pair<SHADER_TYPE, DynamicStruct*> data = *itr;

				DynamicStruct* buff = data.second;

				pipelineState.attachResource(buff, buff->getName(), 0, SHADER_RESOURCE_TYPE::CONSTANT_BUFFER, data.first, false);
			}

			wrapper->getIOInterface()->assignHookResourceByName("particle_texture", batch->_particleTex);

			wrapper->rebuildPSO(&pipelineState);

			pipelineState.applyState(commandList);

			_particleRenderingShader->execute(commandList);

			commandList->createCommand(std::make_shared<PipelineDrawInstancedCommand::InitData>(particleRenderData->_numIndices, std::get<0>(particleDataTuple)->_particlesToRender->size()),
				GRAPHICS_COMMAND_TYPE::PIPELINE_DRAW_INSTANCED);


			commandList->createCommand(std::make_shared<IResourceBuilder>(), GRAPHICS_COMMAND_TYPE::PIPELINE_RESET);
		}
	}
	);

	regCallback(wrapper);
}