#include "../include/GraphicsRenderer.h"

GraphicsRenderer::GraphicsRenderer(SUPPORTED_GRAPHICS_API api, window *outputWindow)
{
	_graphicsResourcePoolManager = new GraphicsResourcePoolManager();

	GraphicsResourcePoolManagerAccessor::initAccessor(_graphicsResourcePoolManager);
	ActiveAPITypeAccessor::initAccessor(api);

	_graphicsResourcePoolManager->createNewResourcePool("gpu_buffer_pool");
	_graphicsResourcePoolManager->createNewResourcePool("render_target_pool");
	_graphicsResourcePoolManager->createNewResourcePool("texture_pool");
	_graphicsResourcePoolManager->createNewResourcePool("texture_sampler_pool");

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
 
		GraphicsResourcePoolManagerAccessor::poolManager->getPool("render_target_pool")->
			addResource(frameBufferRT, "framebuffer", true);
	}
}


GraphicsRenderer::~GraphicsRenderer()
{
	if(_graphicsResourcePoolManager != nullptr)
		delete _graphicsResourcePoolManager;
	if (_dxManager != nullptr)
		delete _dxManager;

	meshFactory::destroyLibrary();
}

void GraphicsRenderer::attachPrimaryCamera(camera * cam)
{
	_primaryCamera = cam;
}

void GraphicsRenderer::renderSolidumObject(SolidumObject * obj)
{
	Shader* objShader = obj->getShader();

	if (objShader != nullptr) {
		if(_primaryCamera != nullptr)
		objShader->updateCameraUniforms(_primaryCamera);
	}

	obj->draw();
}

void GraphicsRenderer::renderLight(Light * light)
{
	if (light->getShader() != nullptr) {

		if (_primaryCamera != nullptr)
		light->getShader()->updateCameraUniforms(_primaryCamera);

		light->getShader()->updateLightUniforms(light);

		light->getShader()->updateGPU();

		light->getShader()->execute(6);
	}
}

