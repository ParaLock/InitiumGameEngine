#include "../include/GraphicsCore.h"

GraphicsCore* GraphicsCore::singletonInstance = nullptr;

GraphicsCore * GraphicsCore::getInstance()
{
	return singletonInstance;
}


GraphicsCore::GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, 
	TaskTree* masterTaskTree, ResourceCreator& resCreator, IEngineInstance* sysInstance) :
		_resourceCreator(resCreator)
{	
	if (singletonInstance == nullptr)
		singletonInstance = this;
	else
		return;

	EventFrameworkCore::getInstance()->registerGlobalEventHub(new EventHub(), "RenderFlowGraphEventHub");

	ActiveGraphicsAPI::setCurrentAPI(api);

	_sysInstance = sysInstance;

	_endFrameState = new GPUPipeline();

	_primaryTaskTree = masterTaskTree;

	EventFrameworkCore::getInstance()->getGlobalEventHub("ComponentEventHub")->subscribeListener(this);

	if (api == SUPPORTED_GRAPHICS_API::DIRECTX11) {

		PipelineFunctions::pipeline_bindBuffer = dx11_bind_shader_buffer;
		PipelineFunctions::pipeline_bindConstantBuffer = dx11_bind_shader_constant_buffer;
		PipelineFunctions::pipeline_bindInputLayout = dx11_bind_shader_input_layout;
		PipelineFunctions::pipeline_bindTexture = dx11_bind_shader_texture;
		PipelineFunctions::pipeline_bindTextureSampler = dx11_bind_shader_texture_sampler;
		PipelineFunctions::pipeline_set_blend_state = dx11_set_blend_state;
		PipelineFunctions::pipeline_setPrimitiveTopology = dx11_set_primitive_topology;
		PipelineFunctions::pipeline_set_depth_test_state = dx11_set_depth_test_state;
		PipelineFunctions::pipeline_bindRenderTargetAsSR = dx11_bind_render_target_as_sr;
		PipelineFunctions::pipeline_bindRenderTargetAsRT = dx11_bind_render_targets_as_rt;
		PipelineFunctions::pipeline_swap_frame = dx11_pipeline_swapframe;
		PipelineFunctions::pipeline_reset = dx11_reset_pipeline;

		PipelineFunctions::pipeline_set_raster_state = dx11_set_raster_state;
		PipelineFunctions::pipeline_drawIndexed = dx11_pipeline_draw_indexed;
		PipelineFunctions::pipeline_drawInstanced = dx11_pipeline_draw_instanced;

		PipelineFunctions::pipeline_set_viewport = dx11_set_viewport;

		_dxManager = new dxDeviceManager();

		dxConfigBlock dxConfig;

		dxConfig.swapchain.Height = outputWindow->screen_height;
		dxConfig.swapchain.Width = outputWindow->screen_width;
		dxConfig.swapchain.OutputWindow = outputWindow->hWnd;

		_dxManager->dxCreateDev(&dxConfig);

		dxDeviceAccessor::initAccessor(_dxManager);

		Viewport frameBuffDepthStencilView = Viewport(outputWindow->screen_height, outputWindow->screen_width, 1, 0);

		RenderTarget* frameBufferRT = (RenderTarget*)resCreator.createResourceImmediate<RenderTarget>
			(&RenderTarget::InitData(TEX_FORMAT::INVALID, outputWindow->screen_height, outputWindow->screen_width),
				"framebuffer", [=](IResource* res) {ResourceUtils::addResourceToGroup(res, std::string("RenderTargetGroup"), sysInstance); });

		frameBufferRT->setViewport(frameBuffDepthStencilView);

		frameBufferRT->updateParameter("RENDERTARGET", dxDeviceAccessor::dxEncapsulator->getFrameBufferRenderTarget());
		frameBufferRT->updateParameter("SHADERVIEW", dxDeviceAccessor::dxEncapsulator->getFrameBufferTexture());

		RenderTarget* depthBufferRT = (RenderTarget*)resCreator.createResourceImmediate<RenderTarget>
			(&RenderTarget::InitData(TEX_FORMAT::INVALID, outputWindow->screen_height, outputWindow->screen_width),
				"depthbuffer", [=](IResource* res) {ResourceUtils::addResourceToGroup(res, std::string("RenderTargetGroup"), sysInstance); });

		depthBufferRT->setViewport(frameBuffDepthStencilView);

		depthBufferRT->updateParameter("TEXTURE", dxDeviceAccessor::dxEncapsulator->getDepthBufferTexture());
		depthBufferRT->updateParameter("SHADERVIEW", dxDeviceAccessor::dxEncapsulator->getDepthBufferShaderView());

		ResourceUtils::createResourceGroup(std::string("RenderTargetGroup"), _sysInstance);

		ResourceUtils::lookupResource(std::string("depthbuffer"), std::string("RenderTargetGroup"), _sysInstance);
	}

	IGraphicsCore::singletonInstance = this;
}


GraphicsCore::~GraphicsCore()
{
	if (_dxManager != nullptr)
		delete _dxManager;
}

void GraphicsCore::beginRender(GraphicsCommandList * endscenePipeline, GraphicsCommandList * scenePipeline, RenderDataGroup * renderData)
{
	renderData->setGlobalData(_globalRenderData);

	for each(Renderer* renderer in _registeredRenderers) {

		renderer->renderScene(scenePipeline, renderData);

	}

	_endFrameState->applyState(endscenePipeline);
}

void GraphicsCore::endRender(GraphicsCommandList * endscenePipeline, GraphicsCommandList * scenePipeline)
{
	_resourceCreator.loadPendingResources();
	_resourceCreator.waitForCompletionOfCreationTask();

	scenePipeline->executeCommands();
	endscenePipeline->executeCommands();
}

void GraphicsCore::setCurrentRenderingCamera(CameraComponent * cam)
{
	_globalRenderData.global_cam._eyePosition = cam->getPos();
	_globalRenderData.global_cam._orthoProjection = cam->getOrthoProjectionMatrix();
	_globalRenderData.global_cam._projectionMatrix = cam->getProjectionMatrix();
	_globalRenderData.global_cam._startView = cam->getStartViewMatrix();
	_globalRenderData.global_cam._viewMatrix = cam->getViewMatrix();
	_globalRenderData.global_cam._worldMatrix = cam->getWorldMatrix();
}

void GraphicsCore::onEvent(EVENT_PTR evt)
{
}

