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
#include "../../SolidumObject/Objects/include/SolidumObject.h"

#include "../../../ResourceManagement/include/ResourceManagerPool.h"

class GraphicsCore
{
private:

	RenderQueue *_renderQueue = nullptr;

	camera* _primaryCamera;

	dxDeviceManager *_dxManager = nullptr;

	ResourceManagerPool *_resManagerPool = nullptr;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void RenderAll();

	void attachPrimaryCamera(camera* cam);

	RenderQueue* getRenderQueue() { return _renderQueue; }

	camera* getPrimaryCamera() { return _primaryCamera; };
};

