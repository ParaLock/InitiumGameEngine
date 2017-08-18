#pragma once

#include "../common.h"

class GPUPipelineOP;
class IGPUBuffer;
class ShaderUniformGroup;
class IShader;

class GPUPipelineOP;

class IGPUPipeline {
private:
public:

	virtual void setRasterState(RASTER_STATE state) = 0;
	virtual void setDepthTestState(DEPTH_TEST_STATE state) = 0;
	virtual void setBlendState(BLEND_STATE state) = 0;

	virtual void setDrawModeIndexed(int indexCount) = 0;
	virtual void setDrawModeInstanced(int instanceCount, int numIndices) = 0;

	virtual void addInstanceBuffer(IGPUBuffer* instanceBuff, IGPUBuffer* geoBuff, size_t instBuffStride, size_t vertexBuffStride) = 0;

	virtual void setPipelineStateResetAtCompletion(bool state) = 0;

	virtual void setShader(IShader* shader) = 0;
	virtual void addShaderUniformGroup(ShaderUniformGroup& group) = 0;

	virtual void applyState(IGraphicsCommandBlock* commandBlock) = 0;

	virtual void reset() = 0;
};