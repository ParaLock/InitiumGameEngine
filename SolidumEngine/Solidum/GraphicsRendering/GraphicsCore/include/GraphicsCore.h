#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Lights/include/Light.h"

#include "../../../EntityFramework/Entity/include/IEntity.h"

#include "../../../EventFramework/include/IEventListener.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"
#include "../../PipelineCommands/include/PipelineFunctions.h"

#include "../../PipelineCommands/include/PipelineCommand.h"

#include "../../Renderer/include/Renderer.h"

#include "../../RenderFlowGraph/include/RenderFlowGraph.h"

#include "../../../PhysicsFramework/include/BoundingSphere.h"

#include "../../../TaskFramework/include/TaskTree.h"

#include "../../../../SolidumAPI/core_interfaces/IEngineInstance.h"

#include "../../RenderPass/include/RenderPassPluginWrapper.h"

#include "IGraphicsCore.h"

class BoundingSphere;

class GraphicsCore : public IEventListener, public IGraphicsCore
{
private:
	std::map<std::string, RenderPassPluginWrapper*> _registeredRenderPasses;
	std::list<Renderer*> _registeredRenderers;

	ResourceCreator& _resourceCreator;

	dxDeviceManager *_dxManager = nullptr;

	TaskTree* _primaryTaskTree;

	GPUPipeline* _endFrameState;

	std::map<DEFAULT_SHADER_TYPE, Shader*> _defaultShaders;

	std::vector<Renderer*> _sortedRenderers;

	RenderFlowGraph* _primaryFlowGraph;

	RenderData_GlobalData _globalRenderData;

	IEngineInstance* _sysInstance;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, 
		TaskTree* masterTaskTree, ResourceCreator& resCreator, IEngineInstance* sysInstance);

	~GraphicsCore();

	void registerRenderPass(RenderPassPluginWrapper* renderpass) { _registeredRenderPasses.insert({renderpass->name(), renderpass}); };

	void registerRenderer(Renderer* renderer) { _registeredRenderers.push_back(renderer); }

	void beginRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline, RenderDataGroup* renderData);

	void endRender(GraphicsCommandList* endscenePipeline, GraphicsCommandList* scenePipeline);

	void setCurrentRenderingCamera(CameraComponent* cam);

	void onEvent(EVENT_PTR evt);

	TaskTree* getPrimaryTaskTree() { return _primaryTaskTree; };
	
	void setWorldBoundingSphere(BoundingSphere* boundingSphere) { _globalRenderData.boundingSphere = boundingSphere; }

	GPUPipeline* getEndscenePSO() { return _endFrameState; }

	RenderPassPluginWrapper* getRegisteredRenderPass(std::string name) { return _registeredRenderPasses.at(name); };

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

