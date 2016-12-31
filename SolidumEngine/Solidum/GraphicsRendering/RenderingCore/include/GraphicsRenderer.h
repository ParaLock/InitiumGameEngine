#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"
#include "../../GraphicsResourcePool/include/GraphicsResourcePoolManager.h"
#include "../../GraphicsResourcePool/include/GraphicsResourcePoolManagerAccessor.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "ActiveAPITypeAccessor.h"

class GraphicsRenderer
{
private:
	SUPPORTED_GRAPHICS_API _apiInUse;

	GraphicsResourcePoolManager *_graphicsResourcePoolManager = nullptr;

	dxDeviceManager *_dxManager = nullptr;
public:
	GraphicsRenderer(SUPPORTED_GRAPHICS_API api, window *outputWindow);
	~GraphicsRenderer();
};

