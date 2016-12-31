#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../Shaders/include/ShaderGeneralDataBuffer.h"


enum GPUPipelineElementParentShader {
	SOL_VS,
	SOL_PS,
	SOL_NON
};

enum GPUPipelineElementType {
	SOL_RENDER_TARGET,
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
	SOL_BLENDING
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
	void *pTarget;

	GPUPipelineElementType targetType;

	GPUPipelineSupportedOP type;

	bool deferred;
};

class GPUPipeline
{
private:
	int renderTargetResNumCounter = 0;
	int samplerResNumCounter = 0;
	int generalShaderDataBufferResNumCounter = 0;

	int notANullPointerValue = -1;
	int *notANullPointer = &notANullPointerValue;

protected:
	std::map<std::string, GPUPipelineElement*> *_elementList;
	std::list<GPUPipelineOP*> *_opList;
	std::map<std::string, ShaderGeneralDataBuffer*> *_generalDataVarToBuffHash;

	bool blendingEnabled;
	bool depthTestEnabled;

public:
	GPUPipeline();
	~GPUPipeline();

	void attachOP(void *pOpTarget, GPUPipelineSupportedOP opType, GPUPipelineElementType opTargetType, bool executionContext);

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
	void attachGeneralShaderDataBuffer(ShaderGeneralDataBuffer* generalBuff, std::string name, GPUPipelineElementParentShader parentShader);

	virtual void use();
	virtual void draw(int numIndices);
};

