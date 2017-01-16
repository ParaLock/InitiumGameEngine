#include "../include/GraphicsCore.h"

GraphicsCore::GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool)
{
	ActiveGraphicsAPI::setCurrentAPI(api);

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
	auto* allActiveShaders = _resManagerPool->getResourceManager("ShaderManager")->getResourceMap();

	for (auto itr = allActiveShaders->begin(); itr != allActiveShaders->end(); itr++) {

		Shader *pShader = itr->second->getCore<Shader>();

		pShader->updateCameraUniforms(_primaryCamera);
	}

	std::list<SolidumObject*>& objectList = _renderQueue->getSolidumObjectQueue();

	for (auto itr = objectList.begin(); itr != objectList.end(); itr++) {
		SolidumObject* currentObj = *itr;

		currentObj->getShader()->updateCameraUniforms(_primaryCamera);


		currentObj->draw();
	}

	std::list<Light*>& lightsList = _renderQueue->getLightQueue();

	for (auto itr = lightsList.begin(); itr != lightsList.end(); itr++) {
		Light* currentLight = *itr;

		currentLight->getShader()->updateLightUniforms(currentLight);

		currentLight->getShader()->updateCameraUniforms(_primaryCamera);

		currentLight->getShader()->updateGPU();

		currentLight->getShader()->execute(6);
	}
}

void GraphicsCore::attachPrimaryCamera(camera* cam)
{
	_primaryCamera = cam;
}

