#pragma once
#include "../../RenderNode/include/RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"

#include "Particle.h"
#include "ParticleStream.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

struct ParticleEmitterRenderNodeParams : public UniqueRenderParams {

	int _maxParticles = 0;

	IShader* _particleRenderShader = nullptr;
	ParticleStream* _particles = nullptr;
	GPUBuffer* _particleInstanceBuffer = nullptr;
};

class ParticleRenderNode : public RenderNode
{
private:
	struct ParticleInstanceData {
		
		Vector2f _texOffset1;
		Vector2f _texOffset2;
		Vector2f _texCoordInfo;
		Matrix4f _mvMatrix;

	};

	ParticleInstanceData* _particleDataCPUBuffer;
public:
	ParticleRenderNode();
	~ParticleRenderNode();

	struct InitData : public IResourceBuilder {
		IShader* _shader;
		ParticleStream* _particles;
		int _maxParticles;

		InitData(IShader* shader, ParticleStream* particles, int maxConcurrentParticles) {
			_shader = shader;
			_particles = particles;
			_maxParticles = maxConcurrentParticles;
		}
	};

	void load(std::shared_ptr<IResourceBuilder> builder);
	void unload();

	void updateParameter(std::string varName, void *data) {};
	void* getParameter(std::string varName) { return nullptr; };

	bool isRenderViable();

	Matrix4f createParticleMVMatrix(Vector3f pos, float rotation, float scale);

	void render();
};

