#pragma once
#include "../../../EngineUtils/include/Vector4.h"

class camera;
class Transform;

struct GlobalRenderingParams {
	Vector4f _ambientLightLevel;
	camera* _globalRenderingCamera;
};

struct LocalRenderingParams {
	bool _useForwardRendering;
	camera* _renderCamera;

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
	void setGlobalParam_GlobalRenderingCamera(camera* cam) { global_params._globalRenderingCamera = cam; }

	Vector4f getGlobalParam_AmbientLight() { return global_params._ambientLightLevel; }
	camera* getGlobalParam_GlobalRenderingCamera() { return global_params._globalRenderingCamera; }

	void setPerNodeParam_RenderCamera(camera* cam) { local_params._renderCamera = cam; };
	void setPerNodeParam_ForwardRendering(bool enable) { local_params._useForwardRendering = enable; };
	void setPerNodeParam_Transform(Transform* transform) { local_params._transform = transform; };

	camera* getPerNodeParam_RenderCamera() { return local_params._renderCamera; };
	bool getPerNodeParam_ForwardRendering() { return local_params._useForwardRendering; }
	Transform* getPerNodeParam_Transform() { return local_params._transform; }

	GlobalRenderingParams getAllGlobalParams() { return global_params; };
	LocalRenderingParams getAllLocalParams() { return local_params; };

	void setAllGlobalParams(GlobalRenderingParams params) { global_params = params; }
	void setAllLocalParams(LocalRenderingParams params) { local_params = params; }
};

