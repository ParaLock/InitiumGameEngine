#pragma once
#include "../../../sysInclude.h"

class mesh;
class Texture;
class MaterialPass;
class ILight;
class Transform;
class camera;
class GPUPipeline;

class IShader {
public:
	virtual void setMesh(mesh* newMesh) = 0;

	virtual void setModelTexture(Texture* tex) = 0;

	virtual void updateMaterialPassUniforms(MaterialPass* pass) = 0;
	virtual void updateLightUniforms(ILight* light) = 0;
	virtual void updateModelUniforms(Transform* transform) = 0;
	virtual void updateCameraUniforms(camera* cam) = 0;

	virtual void updateUniform(std::string varName, void * pData) = 0;
	virtual void updateGPU() = 0;

	virtual void attachPipeline(GPUPipeline* pipe) = 0;
	virtual GPUPipeline* getPipeline() = 0;

	virtual void execute(int numIndices) = 0;

	virtual SHADER_RENDER_TYPE getRenderMode() = 0;
};