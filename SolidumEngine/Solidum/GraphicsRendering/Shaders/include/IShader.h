#pragma once
#include "../../../sysInclude.h"

class mesh;
class Texture;
class MaterialPass;
class ILight;
class Transform;
class CameraComponent;
class GPUPipeline;
class IResource;
class GraphicsCommandList;

class IShader {
public:
	virtual void setMesh(mesh* newMesh) = 0;

	virtual void setModelTexture(Texture* tex) = 0;

	virtual void setMiscResourceHook(IResource* res, std::string name) = 0;

	virtual void updateMaterialPassUniforms(MaterialPass* pass) = 0;
	virtual void updateDeferredLightUniforms(ILight* light) = 0;

	virtual void updatePointLightsForwardRendering(std::vector<ILight*> pointLights) = 0;
	virtual void updateDirectionalLightsForwardRendering(std::vector<ILight*> dirLights) = 0;

	virtual void updateModelUniforms(Transform* transform) = 0;
	virtual void updateCameraUniforms(CameraComponent* cam) = 0;

	virtual void updateUniform(std::string varName, void * pData) = 0;
	virtual void updateGPU() = 0;

	virtual void attachPipeline(GPUPipeline* pipe) = 0;
	virtual GPUPipeline* getPipeline() = 0;

	virtual void execute(GraphicsCommandList* commandList) = 0;

	virtual SHADER_RENDER_TYPE getRenderMode() = 0;
};