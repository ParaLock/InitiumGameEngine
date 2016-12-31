#pragma once
#include "../../../sysInclude.h"
#include "../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../RenderTarget/include/RenderTarget.h"
#include "../../Textures/include/Texture.h"
#include "../../Textures/include/TextureSampler.h"
#include "../../Shaders/include/ShaderInputLayout.h"
#include "../../Shaders/include/ShaderGeneralDataBuffer.h"

class GPUPipelineElement {
public:
	std::string name;
	std::string type;
	std::string parentShader;
	std::string resourcePoolID;

	int resourceSlot;
	bool isOutput;

	void * core;
};

class GPUPipelineOP {
public:
	void *pTarget;

	std::string targetType;

	std::string type;

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

	void attachOP(void *pOpTarget, std::string opType, std::string opTargetName, std::string opTargetType, std::string executionContext);

	void setDepthTest(bool enable);
	void setBlending(bool enable);

	void updateCPUGeneralDataVar(std::string varName, void *pData);
	void syncGeneralDataVars();

	void setVertexBuffer(GPUBuffer *newBuff);
	void setIndexBuffer(GPUBuffer *newBuff);
	void setPrimaryTexture(Texture *newTex);
	void setSecondaryTexture(Texture *newTex);

	void attachTextureHook(std::string name, std::string parentShader);
	void attachBufferHook(std::string name, std::string parentShader);

	void attachRenderTarget(RenderTarget* renderTarget, std::string name, std::string parentShader, bool isOutput);
	void attachTextureSampler(TextureSampler *texSampler, std::string name, std::string parentShader);
	void attachShaderInputLayout(ShaderInputLayout *inputLayout, std::string name);
	void attachGeneralShaderDataBuffer(ShaderGeneralDataBuffer* generalBuff, std::string name, std::string parentShader);

	virtual void use();
	virtual void draw(int numIndices);
};

