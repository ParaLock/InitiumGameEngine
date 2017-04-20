#pragma once
#include "../../RenderNode/include/RenderNode.h"

#include "../../Mesh/include/mesh.h"
#include "../../Textures/include/Texture.h"
#include "../../Shaders/include/Shader.h"

#include "Particle.h"
#include "ParticleStream.h"

#include "../../../ResourceFramework/include/IResourceBuilder.h"

struct ParticleEmitterRenderNodeParams : public UniqueRenderParams {
	IShader* _particleRenderShader = nullptr;
	ParticleStream* _particles = nullptr;

	GPUBuffer* _particleInstanceBuffer = nullptr;

	std::map<ParticleShape, mesh*> _particleMeshCache;
};

class ParticleRenderNode : public RenderNode
{
private:
public:
	ParticleRenderNode();
	~ParticleRenderNode();

	struct ParticleInstanceData {
		Vector3f _position;
	};

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

	void render();
};

