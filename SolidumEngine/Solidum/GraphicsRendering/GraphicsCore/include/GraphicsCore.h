#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Lights/include/Light.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../../EntityFramework/Entity/include/IEntity.h"

#include "../../../EventFramework/include/IEventListener.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"
#include "../../PipelineCommands/include/PipelineFunctions.h"

#include "../../PipelineCommands/include/PipelineCommand.h"

#include "../../GraphicsCommand/include/GraphicsCommandPool.h"

#include "../../Particles/include/ParticlePool.h"
#include "../../Particles/include/ParticleFactory.h"

#include "../../RenderPass/include/RenderPassWrapper.h"

#include "../../Renderer/include/Renderer.h"

#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../../PhysicsFramework/include/BoundingSphere.h"

#include "../../../TaskFramework/include/TaskTree.h"

#include "IGraphicsCore.h"

class ParticlePool;
class BoundingSphere;

class GraphicsCore : public IEventListener, public IGraphicsCore
{
private:
	std::map<std::string, std::shared_ptr<RenderPassWrapper>> _registeredRenderPasses;
	std::list<Renderer*> _registeredRenderers;

	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	TaskTree* _primaryTaskTree;

	GPUPipeline* _endFrameState;

	std::map<DEFAULT_SHADER_TYPE, Shader*> _defaultShaders;

	std::vector<Renderer*> _sortedRenderers;

	RenderFlowGraph* _primaryFlowGraph;

	GraphicsCommandFactory* _graphicsCommandFactory;
	GraphicsCommandPool* _graphicsCommandPool;

	ParticleFactory* _particleFactory;
	ParticlePool* _particlePool;

	RenderData_GlobalData _globalRenderData;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool, TaskTree* masterTaskTree);
	~GraphicsCore();

	void registerRenderPass(std::shared_ptr<RenderPassWrapper> renderpass) { _registeredRenderPasses.insert({renderpass->getName(), renderpass}); };

	void registerRenderer(Renderer* renderer) { _registeredRenderers.push_back(renderer); }

	void beginRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline, RenderDataGroup* renderData);

	void endRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline);

	void setCurrentRenderingCamera(CameraComponent* cam);

	void onEvent(EVENT_PTR evt);

	GraphicsCommandPool* getGraphicsCommandPool() { return _graphicsCommandPool; };
	GraphicsCommandFactory* getGraphicsCommandFactory() { return _graphicsCommandFactory; }

	TaskTree* getPrimaryTaskTree() { return _primaryTaskTree; };

	ParticlePool* getParticlePool() { return _particlePool; }

	void setWorldBoundingSphere(BoundingSphere* boundingSphere) { _globalRenderData.boundingSphere = boundingSphere; }

	GPUPipeline* getEndscenePSO() { return _endFrameState; }

	std::shared_ptr<RenderPassWrapper> getRegisteredRenderPass(std::string name) { return _registeredRenderPasses.at(name); };

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

