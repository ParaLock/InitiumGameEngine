#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"

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
#include "../../PipelineCommand/include/PipelineFunctions.h"

#include "../../PipelineCommand/include/PipelineCommand.h"
#include "../../PipelineCommandQueue/include/PipelineCommandQueue.h"

class GraphicsCore : public IEventListener
{
private:
	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	RenderNodeTree *_renderTree;

	GlobalRenderingParams _globalRenderingParameters;

	PipelineCommandQueue* _primaryPipelineCommandQueue;

	GPUPipeline* _endFrameState;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void beginFrame();

	void endFrame();

	void render();

	void setCurrentRenderingCamera(CameraComponent* cam);

	void onEvent(EVENT_PTR evt);

	void setEndFrameHandler(GPUPipeline* pipe);

	RenderNodeTree* getRenderNodeTree() { return _renderTree; };

	PipelineCommandQueue* getPipelineCommandQueue() { return _primaryPipelineCommandQueue; }

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

