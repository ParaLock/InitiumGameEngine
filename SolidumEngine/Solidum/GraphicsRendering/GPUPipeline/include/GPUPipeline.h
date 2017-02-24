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

#include "../../../EngineUtils/include/StringManipulation.h"

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

	std::map<std::string, DynamicStruct*> *_constantBufferMemberNameMap;
	std::map<std::string, GPUPipelineElement*> *_elementList;
	std::list<GPUPipelineOP*> *_opList;

	BLEND_STATE blendState = BLEND_STATE::BLENDING_OFF;
	DEPTH_TEST_STATE depthState = DEPTH_TEST_STATE::FULL_DISABLE;
	RASTER_STATE rasterState = RASTER_STATE::NORMAL;

public:
	GPUPipeline();
	~GPUPipeline();

	virtual void load(IResourceBuilder* builder);
	virtual void unload();

	void reset();

	void attachOP(GPUPipelineSupportedOP opType, std::string targetName, GPUPipelineElementType opTargetType, bool executionContext);

	void setRasterState(RASTER_STATE state);
	void setDepthTestState(DEPTH_TEST_STATE state);
	void setBlendState(BLEND_STATE state);

	void setHookResource(IResource* res, std::string name);

	void attachResource(IResource* res, std::string name, GPUPipelineElementType type,
		GPUPipelineElementParentShader parentShader, bool isOutput);


	virtual void applyState() = 0;
	virtual void executePass(int numIndices) = 0;

	std::map<std::string, DynamicStruct*>* getVarToBuffMap() { return _constantBufferMemberNameMap; };
};

