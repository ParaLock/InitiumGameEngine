#pragma once

#include "../../../sysInclude.h"

class RenderNodeTree;
class CameraComponent;
class Shader;
class GPUPipeline;
class RenderNodePool;
class GraphicsCommandPool;
class GraphicsCommandFactory;
class ParticlePool;
class World;
class Renderer;

class IGraphicsCore
{
public:
	IGraphicsCore();
	~IGraphicsCore();

	virtual void beginFrame() = 0;

	virtual void endFrame() = 0;

	virtual void render() = 0;

	virtual void setCurrentRenderingCamera(CameraComponent* cam) = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	virtual void registerRenderer(Renderer* newRenderer) = 0;

	virtual GPUPipeline* getEndscenePSO() = 0;

	virtual RenderNodeTree* getRenderNodeTree() = 0;
	virtual RenderNodePool* getRenderNodePool() = 0;

	virtual GraphicsCommandPool* getGraphicsCommandPool() = 0;
	virtual GraphicsCommandFactory* getGraphicsCommandFactory() = 0;

	virtual ParticlePool* getParticlePool() = 0;

	static IGraphicsCore* singletonInstance;
	static IGraphicsCore* getInstance();
};

