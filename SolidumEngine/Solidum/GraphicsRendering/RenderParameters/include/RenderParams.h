#pragma once
#include "../../../EngineUtils/include/Vector4.h"

class CameraComponent;
class Transform;

struct GlobalRenderingParams {
	Vector4f _ambientLightLevel;
	CameraComponent* _globalRenderingCamera;
};

struct LocalRenderingParams {
	bool _useForwardRendering;
	CameraComponent* _renderCamera;

	bool _depthTestEnabled;
	bool _isVisible;

	Vector4f _skydomeApexColor;
	Vector4f _skydomeCenterColor;

	Transform* _transform;
};

class RenderParams
{
private:
	GlobalRenderingParams global_params;
	LocalRenderingParams local_params;
public:
	RenderParams();
	~RenderParams();

	void setGlobalParam_AmbientLight(Vector4f color) { global_params._ambientLightLevel = color; };
	void setGlobalParam_GlobalRenderingCamera(CameraComponent* cam) { global_params._globalRenderingCamera = cam; }

	void setPerNodeParam_skydomeCenterColor(Vector4f color) { local_params._skydomeCenterColor = color; };
	void setPerNodeParam_skydomeApexColor(Vector4f cam) { local_params._skydomeApexColor = cam; }

	Vector4f getGlobalParam_AmbientLight() { return global_params._ambientLightLevel; }
	CameraComponent* getGlobalParam_GlobalRenderingCamera() { return global_params._globalRenderingCamera; }

	Vector4f getPerNodeParam_skydomeCenterColor() { return local_params._skydomeCenterColor; };
	Vector4f getPerNodeParam_skydomeApexColor() { return local_params._skydomeApexColor; }

	void setPerNodeParam_RenderCamera(CameraComponent* cam) { local_params._renderCamera = cam; };
	void setPerNodeParam_ForwardRendering(bool enable) { local_params._useForwardRendering = enable; };
	void setPerNodeParam_Transform(Transform* transform) { local_params._transform = transform; };
	void setPerNodeParam_DepthTestEnableState(bool depthTest) { local_params._depthTestEnabled = depthTest; }

	void setPerNodeParam_isVisible(bool isVisible) { local_params._isVisible = isVisible; }

	CameraComponent* getPerNodeParam_RenderCamera() { return local_params._renderCamera; };
	bool getPerNodeParam_ForwardRendering() { return local_params._useForwardRendering; }
	Transform* getPerNodeParam_Transform() { return local_params._transform; }
	bool getPerNodeParam_DepthTestEnableState() { return local_params._depthTestEnabled; }
	bool getPerNodeParam_isVisible() { return local_params._isVisible; }

	GlobalRenderingParams getAllGlobalParams() { return global_params; };
	LocalRenderingParams getAllLocalParams() { return local_params; };

	void setAllGlobalParams(GlobalRenderingParams params) { global_params = params; }
	void setAllLocalParams(LocalRenderingParams params) { local_params = params; }
};

