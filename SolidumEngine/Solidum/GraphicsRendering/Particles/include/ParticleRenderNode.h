#pragma once
#include "../../RenderNode/include/RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"

#include "Particle.h"
#include "ParticleStream.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

struct ParticleEmitterRenderNodeParams : public UniqueRenderParams {

	int _maxParticles = 0;

	ParticleStream* _particles = nullptr;
	GPUBuffer* _particleInstanceBuffer = nullptr;
	ParticleInstanceData* _particleDataCPUBuffer = nullptr;

};

class ParticleRenderNode : public RenderNode
{
private:
public:
	ParticleRenderNode();
	~ParticleRenderNode();

	struct InitData : public IResourceBuilder {
		ParticleStream* _particles;
		int _maxParticles;

		InitData(ParticleStream* particles, int maxConcurrentParticles) {
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

