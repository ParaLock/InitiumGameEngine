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

	Vector4f getGlobalParam_AmbientLight() { return global_params._ambientLightLevel; }
	CameraComponent* getGlobalParam_GlobalRenderingCamera() { return global_params._globalRenderingCamera; }

	void setPerNodeParam_RenderCamera(CameraComponent* cam) { local_params._renderCamera = cam; };
	void setPerNodeParam_ForwardRendering(bool enable) { local_params._useForwardRendering = enable; };
	void setPerNodeParam_Transform(Transform* transform) { local_params._transform = transform; };
	void setPerNodeParam_DepthTestEnableState(bool depthTest) { local_params._depthTestEnabled = depthTest; }

	CameraComponent* getPerNodeParam_RenderCamera() { return local_params._renderCamera; };
	bool getPerNodeParam_ForwardRendering() { return local_params._useForwardRendering; }
	Transform* getPerNodeParam_Transform() { return local_params._transform; }
	bool getPerNodeParam_DepthTestEnableState() { return local_params._depthTestEnabled; }

	GlobalRenderingParams getAllGlobalParams() { return global_params; };
	LocalRenderingParams getAllLocalParams() { return local_params; };

	void setAllGlobalParams(GlobalRenderingParams params) { global_params = params; }
	void setAllLocalParams(LocalRenderingParams params) { local_params = params; }
};

