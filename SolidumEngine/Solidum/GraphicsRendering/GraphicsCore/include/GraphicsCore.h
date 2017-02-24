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

#include "../../../EntityFramework/Entity/include/IEntity.h"

#include "../../../EventFramework/include/IEventListener.h"

#include "../../../EventFramework/include/EventFrameworkCore.h"

#include "../../RenderNodeTree/include/RenderNodeTree.h"

class GraphicsCore : public IEventListener
{
private:
	dxDeviceManager *_dxManager = nullptr;
	ResourceManagerPool *_resManagerPool = nullptr;

	camera* _primaryCamera = nullptr;

	RenderNodeTree _renderTree;

	GlobalRenderingParams _globalRenderingParameters;

public:
	GraphicsCore(SUPPORTED_GRAPHICS_API api, window *outputWindow, ResourceManagerPool* resManagerPool);
	~GraphicsCore();

	void RenderAll();

	void onEvent(EVENT_PTR evt);

	void attachPrimaryCamera(camera* cam);

	std::unique_ptr<RenderNodeTree> getRenderNodeTree() { return std::make_unique<RenderNodeTree>(_renderTree); };
	camera* getPrimaryCamera() { return _primaryCamera; }

	static GraphicsCore* singletonInstance;
	static GraphicsCore* getInstance();
};

