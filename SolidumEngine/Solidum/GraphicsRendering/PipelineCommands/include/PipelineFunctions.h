#pragma once
#include "../../../sysInclude.h"

class PipelineFunctions
{
private:
public:
	PipelineFunctions();
	~PipelineFunctions();

	static std::function<void(int, SHADER_TYPE, void*)> pipeline_bindTexture;
	static std::function<void(int, SHADER_TYPE, void*)> pipeline_bindTextureSampler;
	static std::function<void(int, SHADER_TYPE, void*)> pipeline_bindConstantBuffer;

	static std::function<void(void* rt, SHADER_TYPE parentShader, int bindSlot)> pipeline_bindRenderTargetAsSR;
	static std::function<void(std::vector<void*> renderTargets, bool bindDS)> pipeline_bindRenderTargetAsRT;

	static std::function<void(void*, UINT, BUFFER_TYPE)> pipeline_bindBuffer;
	static std::function<void(void*)> pipeline_bindInputLayout;

	static std::function<void(PRIMITIVE_TOPOLOGY)> pipeline_setPrimitiveTopology;

	static std::function<void(DEPTH_TEST_STATE)> pipeline_set_depth_test_state;
	static std::function<void(BLEND_STATE)> pipeline_set_blend_state;

	static std::function<void(RASTER_STATE)> pipeline_set_raster_state;

	static std::function<void(int, int)> pipeline_drawIndexed;

	static std::function<void()> pipeline_clearDepthStencil;

	static std::function<void(float maxDepth, float minDepth, int width, int height)> pipeline_set_viewport;

	static std::function<void()> pipeline_reset;

	static std::function<void()> pipeline_swap_frame;
};

