#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"

#include "../../Camera/include/camera.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../RenderQueue/include/RenderQueue.h"

#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Lights/include/Light.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/IEventPublisher.h"

#include "../../../EventFramework/include/RenderEvent.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

class GraphicsCore : public IEventListener, public IEventPublisher
{
private:

	RenderQueue *_renderQueue = nullptr;
	camera* _primaryCamera;
	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void onEvent(IEvent* evt);

	void Render(std::string meshID, std::string texID, std::string matID, std::string shaderID, std::string lightID, Transform* transform);

	void attachPrimaryCamera(camera* cam);

	RenderQueue* getRenderQueue() { return _renderQueue; }

	camera* getPrimaryCamera() { return _primaryCamera; };
};

