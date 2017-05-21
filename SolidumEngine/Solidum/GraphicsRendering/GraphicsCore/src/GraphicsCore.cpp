#include "../include/GraphicsCore.h"

GraphicsCore* GraphicsCore::singletonInstance = nullptr;

GraphicsCore * GraphicsCore::getInstance()
{
	return singletonInstance;
}


GraphicsCore::GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool)
{	
	if (singletonInstance == nullptr)
		singletonInstance = this;
	else
		return;

	EventFrameworkCore::getInstance()->registerGlobalEventHub(new EventHub(), "RenderFlowGraphEventHub");

	ActiveGraphicsAPI::setCurrentAPI(api);

	_renderNodeFactory = new RenderNodeFactory();
	_renderNodePool = new RenderNodePool(_renderNodeFactory);

	_graphicsCommandFactory = new GraphicsCommandFactory();
	_graphicsCommandPool = new GraphicsCommandPool(_graphicsCommandFactory);

	_particleFactory = new ParticleFactory();
	_particlePool = new ParticlePool(_particleFactory);

	_renderTree = new RenderNodeTree();

	_gcqManager = new GCLQManager();

	_gcqManager->createCommandQueue("primaryGraphicsCommandQueue");
	_gcqManager->setPrimaryCommandQueue("primaryGraphicsCommandQueue");

	_endFrameState = new GPUPipeline();

	EventFrameworkCore::getInstance()->getGlobalEventHub("ComponentEventHub")->subscribeListener(this);

	_resManagerPool = resManagerPool;

	_globalRenderingParameters._ambientLightLevel = Vector4f(0.2f, 0.2f, 0.2f, 0.2f);

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

		RenderTarget* frameBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getFrameBufferRenderTarget(),
			dxDeviceAccessor::dxEncapsulator->getFrameBufferTexture(),
			frameBuffDepthStencilView);

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(frameBufferRT, "framebuffer");

		RenderTarget* depthBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getDepthBufferShaderView(),
			dxDeviceAccessor::dxEncapsulator->getDepthBufferTexture(),
			frameBuffDepthStencilView);

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(depthBufferRT, "depthbuffer");
	}

	IGraphicsCore::singletonInstance = this;
}


GraphicsCore::~GraphicsCore()
{
	if (_dxManager != nullptr)
		delete _dxManager;
	if (_renderTree != nullptr)
		delete _renderTree;
}

void GraphicsCore::beginFrame()
{
}

void GraphicsCore::endFrame()
{
}

void GraphicsCore::render()
{
	_renderTree->updateGlobalRenderParams(_globalRenderingParameters);
	
	_renderTree->optimize();

	_renderTree->walkTree();

	GraphicsCommandList* primaryCommandList = new GraphicsCommandList();
	GraphicsCommandList* _endsceneCommandList = new GraphicsCommandList();

	for each(Renderer* renderer in _sortedRenderers) {

		renderer->gatherAndPrepareNodes(_renderTree);
		renderer->processNodes(primaryCommandList);
	}

	_endFrameState->applyState(_endsceneCommandList);

	_gcqManager->getPrimaryCommandQueue()->queueCommandList(_endsceneCommandList);
	_gcqManager->getPrimaryCommandQueue()->queueCommandList(primaryCommandList);


	_gcqManager->getPrimaryCommandQueue()->processAllCommands();
}

void GraphicsCore::setCurrentRenderingCamera(CameraComponent* cam)
{
	_globalRenderingParameters._globalRenderingCamera = cam;
}

void GraphicsCore::onEvent(EVENT_PTR evt)
{
}

void GraphicsCore::registerRenderer(Renderer * newRenderer)
{
	_registeredRenderers.insert({newRenderer->getName(), newRenderer});
}

void GraphicsCore::setPrimaryRenderFlowGraph(RenderFlowGraph * graph)
{
	_primaryFlowGraph = graph;
}

void GraphicsCore::calculateRenderOrder()
{
	if (_primaryFlowGraph != nullptr) {

		_sortedRenderers.clear();

		auto& renderOrder = _primaryFlowGraph->getNodeExecutionOrder();

		for each(std::string rendererName in renderOrder) {

			Renderer* activeRenderer = _registeredRenderers.at(rendererName);
			_sortedRenderers.push_back(activeRenderer);
		}
	}
}
