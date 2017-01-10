#pragma once
#include "../../../sysInclude.h"
#include "../../Window/include/window.h"
#include "../../GraphicsResourcePool/include/GraphicsResourcePoolManager.h"
#include "../../GraphicsResourcePool/include/GraphicsResourcePoolManagerAccessor.h"

#include "../../Mesh/include/mesh.h"
#include "../../Lights/include/LightFactory.h"
#include "../../Shaders/include/ShaderFactory.h"

#include "../../Directx11Rendering/dxDevice/include/dxDeviceManager.h"
#include "../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"
#include "ActiveAPITypeAccessor.h"

#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Directx11Rendering/dxRenderTarget/include/dxRenderTarget.h"

#include "../../Mesh/include/meshFactory.h"

#include "../../Camera/include/camera.h"

#include "../../../EngineCore/SolidumObject/Objects/include/SolidumObject.h"

class GraphicsRenderer
{
private:
	camera* _primaryCamera;

	SUPPORTED_GRAPHICS_API _apiInUse;

	GraphicsResourcePoolManager *_graphicsResourcePoolManager = nullptr;

	dxDeviceManager *_dxManager = nullptr;
	RenderTarget* _framebuffer = nullptr;
public:
	GraphicsRenderer(SUPPORTED_GRAPHICS_API api, window *outputWindow);
	~GraphicsRenderer();

	void attachPrimaryCamera(camera* cam);

	void renderSolidumObject(SolidumObject* obj);
	void renderLight(Light* light);
};

