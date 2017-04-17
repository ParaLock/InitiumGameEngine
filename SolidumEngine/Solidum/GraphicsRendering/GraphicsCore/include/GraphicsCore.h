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

#include "../../RenderNodeTree/include/RenderNodeTree.h"

#include "../../GPUPipeline/include/GPUPipeline.h"

#include "../../Directx11Rendering/api_function_wrappers/include/dx11_pipeline_functions_wrapper.h"
#include "../../PipelineCommands/include/PipelineFunctions.h"

#include "../../PipelineCommands/include/PipelineCommand.h"
#include "../../GraphicsCommandListQueue/include/GraphicsCommandListQueue.h"
#include "../../GraphicsCommandListQueueManager/include/GCLQManager.h"

#include "../../RenderNode/include/RenderNodePool.h"
#include "../../GraphicsCommand/include/GraphicsCommandPool.h"

#include "IGraphicsCore.h"

class RenderNodeFactory;
class BoundingSphere;

class GraphicsCore : public IEventListener, public IGraphicsCore
{
private:
	GCLQManager* _gcqManager;

	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	RenderNodeTree *_renderTree;

	GlobalRenderingParams _globalRenderingParameters;

	GPUPipeline* _endFrameState;

	std::map<DEFAULT_SHADER_TYPE, Shader*> _defaultShaders;

	RenderNodeFactory* _renderNodeFactory;
	RenderNodePool* _renderNodePool;

	GraphicsCommandFactory* _graphicsCommandFactory;
	GraphicsCommandPool* _graphicsCommandPool;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void registerDefaultShader(DEFAULT_SHADER_TYPE type, Shader* shader);
	Shader* getDefaultShader(DEFAULT_SHADER_TYPE type);

	void beginFrame();

	void endFrame();

	void render();

	void setCurrentRenderingCamera(CameraComponent* cam);

	void onEvent(EVENT_PTR evt);

	void setEndFrameHandler(GPUPipeline* pipe);

	RenderNodeTree* getRenderNodeTree() { return _renderTree; };
	RenderNodePool* getRenderNodePool() { return _renderNodePool; };

	GraphicsCommandPool* getGraphicsCommandPool() { return _graphicsCommandPool; };
	GraphicsCommandFactory* getGraphicsCommandFactory() { return _graphicsCommandFactory; }

	void setWorldBoundingSphere(BoundingSphere* boundingSphere) { _globalRenderingParameters._worldBoundingSphere = boundingSphere; }

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

