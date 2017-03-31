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
#include "../../GraphicsCommandQueue/include/GraphicsCommandQueue.h"
#include "../../GraphicsCommandQueueManager/include/GCQManager.h"

class GraphicsCore : public IEventListener
{
private:
	GCQManager* _gcqManager;

	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	RenderNodeTree *_renderTree;

	GlobalRenderingParams _globalRenderingParameters;

	GPUPipeline* _endFrameState;

	std::map<DEFAULT_SHADER_TYPE, Shader*> _defaultShaders;

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

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

