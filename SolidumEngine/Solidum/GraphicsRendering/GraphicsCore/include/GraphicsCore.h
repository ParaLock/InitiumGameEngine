#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "../../ActiveGraphicsAPI.h"

#include "../../Camera/include/camera.h"

#include "../../ActiveGraphicsAPI.h"

#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Lights/include/Light.h"

#include "../../../ResourceFramework/include/ResourceManagerPool.h"

#include "../../../EventFramework/include/IEventListener.h"
#include "../../../EventFramework/include/IEventPublisher.h"

#include "../../../EventFramework/include/RenderEvent.h"

#include "../../RenderProcess/include/RenderProcess.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

class GraphicsCore : public IEventListener, public IEventPublisher
{
private:
	camera* _primaryCamera;
	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void RenderAll();

	void onEvent(EVENT_PTR evt);

	void attachPrimaryCamera(camera* cam);

	camera* getPrimaryCamera() { return _primaryCamera; };
};

