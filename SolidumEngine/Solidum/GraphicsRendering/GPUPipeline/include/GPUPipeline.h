#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../../EngineUtils/include/DynamicBuffer.h"

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
	std::string resourcePoolID;

	int resourceSlot;
	bool isOutput;

	void * core;
};

class GPUPipelineOP {
public:
	std::string targetName;

	GPUPipelineElementType targetType;

	GPUPipelineSupportedOP type;

	bool deferred;
};

class GPUPipeline
{
private:
	int renderTargetCount = 0;
	int texSamplerCount = 0;
protected:
	std::string _name;

	std::map<std::string, GPUPipelineElement*> *_elementList;
	std::map<std::string, DynamicBuffer*> *_generalDataVarToBuffHash;
	std::list<GPUPipelineOP*> *_opList;

	bool blendingEnabled;
	bool depthTestEnabled;

public:
	GPUPipeline();
	~GPUPipeline();

	void attachOP(GPUPipelineSupportedOP opType, std::string targetName, GPUPipelineElementType opTargetType, bool executionContext);

	void setDepthTest(bool enable);
	void setBlending(bool enable);

	void updateCPUGeneralDataVar(std::string varName, void *pData);
	void syncGeneralDataVars();

	void setVertexBuffer(GPUBuffer *newBuff);
	void setIndexBuffer(GPUBuffer *newBuff);
	void setPrimaryTexture(Texture *newTex);
	void setSecondaryTexture(Texture *newTex);

	void attachTextureHook(std::string name, GPUPipelineElementParentShader parentShader);
	void attachBufferHook(std::string name, GPUPipelineElementParentShader parentShader);

	void attachRenderTarget(RenderTarget* renderTarget, std::string name, GPUPipelineElementParentShader parentShader, bool isOutput);
	void attachTextureSampler(TextureSampler *texSampler, std::string name, GPUPipelineElementParentShader parentShader);
	void attachShaderInputLayout(ShaderInputLayout *inputLayout, std::string name);
	void attachGeneralShaderDataBuffer(DynamicBuffer* generalBuff, GPUPipelineElementParentShader parentShader);

	virtual void use();
	virtual void draw(int numIndices);
};

