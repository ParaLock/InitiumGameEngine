#include "../include/GraphicsCore.h"

GraphicsCore::GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool)
{
	ActiveGraphicsAPI::setCurrentAPI(api);

	EventFrameworkCore::getInstance()->getGlobalEventHub("ComponentEventHub")->subscribeListener(this);

	_renderQueue = new RenderQueue();
	_primaryCamera = new camera(0.1f, 1000.0f);
	_resManagerPool = resManagerPool;

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
	}
}


GraphicsCore::~GraphicsCore()
{
	if (_dxManager != nullptr)
		delete _dxManager;
	if (_renderQueue != nullptr)
		delete _renderQueue;
}

void GraphicsCore::RenderAll()
{
	using std::placeholders::_1;

	std::function<void(RenderOP)> callback = std::bind(&GraphicsCore::Render, this, _1);

	_renderQueue->processQueuedItems(callback);
}

void GraphicsCore::Render(RenderOP renderOP)
{
	RenderOP op = renderOP;

	op.setCamera(_primaryCamera);

	if (op.getShader() != nullptr) {
		Shader* shader = op.getShader();

		if (op.getLight() != nullptr) {

			shader->updateLightUniforms(op.getLight());

			if (op.getCamera() != nullptr)
				shader->updateCameraUniforms(op.getCamera());

			shader->updateGPU();
			shader->execute(6);
		}
		else if (op.getMesh() != nullptr) {

			if (op.getMesh() != nullptr) {
				shader->setMesh(op.getMesh());

				if (op.getTransform() != nullptr)
					shader->updateModelUniforms(op.getTransform());
			}

			if (op.getTexture() != nullptr)
				shader->setModelTexture(op.getTexture());

			if (op.getMaterial() != nullptr)
				shader->updateMaterialUniforms(op.getMaterial());

			if (op.getCamera() != nullptr)
				shader->updateCameraUniforms(op.getCamera());



			shader->updateGPU();
			shader->execute(op.getMesh()->numIndices);
		}
	}
}

void GraphicsCore::onEvent(EVENT_PTR evt)
{
	RenderEvent* renderEvt;

	switch (evt.get()->getType())
	{
		case EVENT_TYPE::RENDER_EVENT_QUEUE_OP:
			renderEvt = evt.get()->getEvent<RenderEvent>();

			_renderQueue->queueRenderOP(renderEvt->getRenderOP());

			break;
	default:
		break;
	}
}

void GraphicsCore::attachPrimaryCamera(camera* cam)
{
	_primaryCamera = cam;
}

