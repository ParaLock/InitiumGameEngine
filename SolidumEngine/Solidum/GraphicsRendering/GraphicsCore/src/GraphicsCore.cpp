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

void GraphicsCore::onEvent(IEvent * evt)
{
	RenderEvent* renderEvt;

	switch (evt->getType())
	{
		case EVENT_TYPE::RENDER_EVENT:
			renderEvt = evt->getEvent<RenderEvent>();

			Render(renderEvt->getMeshID(), renderEvt->getTexID(), 
				renderEvt->getMatID(), renderEvt->getShaderID(), renderEvt->getLightID(), renderEvt->getTransform());

			break;
	default:
		break;
	}

	delete evt;
}

void GraphicsCore::Render(std::string meshID, std::string texID, 
	std::string matID, std::string shaderID, std::string lightID, Transform* transform)
{
	auto* allActiveShaders = _resManagerPool->getResourceManager("ShaderManager")->getResourceMap();

	for (auto itr = allActiveShaders->begin(); itr != allActiveShaders->end(); itr++) {

		Shader *pShader = itr->second->getCore<Shader>();

		pShader->updateCameraUniforms(_primaryCamera);
	}

	mesh* Mesh;
	Shader* shader;
	Texture* tex;
	Material* mat;
	Light* light;

	if (shaderID != "null") {

		shader = _resManagerPool->getResourceManager("ShaderManager")->getResource(shaderID)->getCore<Shader>();

		if (meshID != "null") {
			Mesh = _resManagerPool->getResourceManager("meshManager")->getResource(meshID)->getCore<mesh>();
			shader->setMesh(Mesh);
		}
		if (texID != "null") {
			tex = _resManagerPool->getResourceManager("TextureManager")->getResource(texID)->getCore<Texture>();
			shader->setModelTexture(tex);
		}
		if (matID != "null") {
			mat = _resManagerPool->getResourceManager("MaterialManager")->getResource(matID)->getCore<Material>();
			shader->updateMaterialUniforms(mat);
		}

		if (lightID != "null") {
			light = _resManagerPool->getResourceManager("LightManager")->getResource(lightID)->getCore<Light>();
			shader->updateLightUniforms(light);
		}

		if (transform != nullptr) {
			shader->updateModelUniforms(transform);
		}

		shader->updateGPU();

		if (meshID != "null") {
			shader->execute(Mesh->numIndices);
		}
		else {
			shader->execute(NULL);
		}
	}	
}

void GraphicsCore::attachPrimaryCamera(camera* cam)
{
	_primaryCamera = cam;
}

