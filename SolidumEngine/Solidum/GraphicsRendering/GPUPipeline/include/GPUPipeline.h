#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../../EngineUtils/include/DynamicStruct.h"

#include "../../../ResourceFramework/include/IResourceManager.h"
#include "../../../ResourceFramework/include/ResourceManagerPool.h"
#include "../../../ResourceFramework/include/IResource.h"

class GPUPipelineBuilder : public IResourceBuilder {
public:
	LPCWSTR _filename;
	ResourceManagerPool* _pResManagerPool;

	GPUPipelineBuilder(LPCWSTR filename, ResourceManagerPool* pResFactoryPool) {
		_filename = filename;
		_pResManagerPool = pResFactoryPool;
	}
};

enum GPUPipelineElementParentShader {
	SOL_VS,
	SOL_PS,
	SOL_NON
};

enum GPUPipelineElementType {
	SOL_RENDER_TARGET,
	SOL_ZBUFFER,
	SOL_GENERAL_DATA_BUFF,
	SOL_MESH_DATA_LAYOUT,
	SOL_SAMPLER,
	SOL_BUFFER_HOOK,
	SOL_TEXTURE_HOOK
};

enum GPUPipelineDataType {
	SOL_MATRIX,
	SOL_FLOAT,
	SOL_FLOAT2,
	SOL_FLOAT3,
	SOL_FLOAT4
};

enum GPUPipelineElementAttrib {
	SOL_OUTPUT,
	SOL_INPUT,
	SOL_WRAP,
	SOL_LINEAR
};

enum GPUPipelineSupportedOP {
	SOL_CLEAR,
	SOL_DEPTH_TEST,
	SOL_BLENDING,
	SOL_SWAPFRAME
};

class GPUPipelineElement {
public:
	std::string name;
	GPUPipelineElementType type;
	GPUPipelineElementParentShader parentShader;

	IResource* core;

	int resourceSlot;
	bool isOutput;
};

class GPUPipelineOP {
public:
	std::string targetName;

	GPUPipelineElementType targetType;
	GPUPipelineSupportedOP type;

	bool deferred;
};

class GPUPipeline : public IResource
{
private:
	int renderTargetCount = 0;
	int texSamplerCount = 0;
protected:

	ResourceManagerPool* _resManagerPool;

	std::map<std::string, DynamicStruct*> *_uniformToBufferMap;
	std::map<std::string, GPUPipelineElement*> *_elementList;
	std::list<GPUPipelineOP*> *_opList;

	bool blendingEnabled;
	bool depthTestEnabled;

public:
	GPUPipeline();
	~GPUPipeline();

	void reset();

	void attachOP(GPUPipelineSupportedOP opType, std::string targetName, GPUPipelineElementType opTargetType, bool executionContext);

	void setDepthTest(bool enable);
	void setBlending(bool enable);

	void setHookResource(IResource* res, std::string name);

	void attachResource(IResource* res, std::string name, GPUPipelineElementType type,
		GPUPipelineElementParentShader parentShader, bool isOutput);


	virtual void applyState();
	virtual void executePass(int numIndices);

	std::map<std::string, DynamicStruct*>* getVarToBuffMap() { return _uniformToBufferMap; };
};

