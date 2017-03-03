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

	ActiveGraphicsAPI::setCurrentAPI(api);

	_renderTree = new RenderNodeTree();

	std::vector<SHADER_RENDER_TYPE> renderExecutionOrder;
	renderExecutionOrder.push_back(SHADER_RENDER_TYPE::FORWARD_RENDERING);
	renderExecutionOrder.push_back(SHADER_RENDER_TYPE::DEFERRED_RENDERING);
	renderExecutionOrder.push_back(SHADER_RENDER_TYPE::DEFERRED_RENDERING_LIGHT);

	_renderTree->setExecutionOrder(renderExecutionOrder);

	EventFrameworkCore::getInstance()->getGlobalEventHub("ComponentEventHub")->subscribeListener(this);

	_resManagerPool = resManagerPool;


	_globalRenderingParameters._ambientLightLevel = Vector4f(0.2f, 0.2f, 0.2f, 0.2f);

	if (api == SUPPORTED_GRAPHICS_API::DIRECTX11) {

		_dxManager = new dxDeviceManager();

		dxConfigBlock dxConfig;

		dxConfig.swapchain.Height = outputWindow->screen_height;
		dxConfig.swapchain.Width = outputWindow->screen_width;
		dxConfig.swapchain.OutputWindow = outputWindow->hWnd;

		_dxManager->dxCreateDev(&dxConfig);

		dxDeviceAccessor::initAccessor(_dxManager);

		RenderTarget* frameBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getFrameBufferRenderTarget(),
			dxDeviceAccessor::dxEncapsulator->getFrameBufferTexture());

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(frameBufferRT, "framebuffer");

		RenderTarget* depthBufferRT = new dxRenderTarget(
			dxDeviceAccessor::dxEncapsulator->getDepthBufferShaderView(),
			dxDeviceAccessor::dxEncapsulator->getDepthBufferTexture());

		resManagerPool->getResourceManager("RenderTargetManager")->addResource(depthBufferRT, "depth_buffer");
	}
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
	_endFrameState->executePass(NULL);
}

void GraphicsCore::render()
{
	beginFrame();

	_renderTree->updateGlobalRenderParams(_globalRenderingParameters);
	
	_renderTree->optimize();

	_renderTree->walkTree();

	endFrame();
}

void GraphicsCore::setCurrentRenderingCamera(CameraComponent* cam)
{
	_globalRenderingParameters._globalRenderingCamera = cam;
}

void GraphicsCore::onEvent(EVENT_PTR evt)
{
}

void GraphicsCore::setEndFrameHandler(GPUPipeline * pipe)
{
	_endFrameState = pipe;
}
