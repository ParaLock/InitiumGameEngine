#pragma once

#include "../../../sysInclude.h"

class CameraComponent;
class Shader;
class GPUPipeline;
class ResourcePool;
class GraphicsCommandList;
class World;
class Renderer;
class TaskTree;
class RenderPassPluginWrapper;
class RenderDataGroup;


class IGraphicsCore
{
public:
	IGraphicsCore();
	~IGraphicsCore();

	virtual void registerRenderer(Renderer* renderer) = 0;
	virtual void registerRenderPass(RenderPassPluginWrapper* renderpass) = 0;

	virtual void beginRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline, RenderDataGroup* renderData) = 0;

	virtual	void endRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline) = 0;

	virtual void setCurrentRenderingCamera(CameraComponent* cam) = 0;

	virtual void onEvent(EVENT_PTR evt) = 0;

	virtual GPUPipeline* getEndscenePSO() = 0;

	virtual TaskTree* getPrimaryTaskTree() = 0;

	virtual RenderPassPluginWrapper* getRegisteredRenderPass(std::string name) = 0;

	static IGraphicsCore* singletonInstance;
	static IGraphicsCore* getInstance();
};

