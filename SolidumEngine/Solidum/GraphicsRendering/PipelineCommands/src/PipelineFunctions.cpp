#include "../include/PipelineFunctions.h"

PipelineFunctions::PipelineFunctions()
{
}


PipelineFunctions::~PipelineFunctions()
{
}

std::function<void(int, SHADER_TYPE, void*)> PipelineFunctions::pipeline_bindTexture;
std::function<void(int, SHADER_TYPE, void*)> PipelineFunctions::pipeline_bindTextureSampler;
std::function<void(int, SHADER_TYPE, void*)> PipelineFunctions::pipeline_bindConstantBuffer;

std::function<void(void* rt, SHADER_TYPE parentShader, int bindSlot)> PipelineFunctions::pipeline_bindRenderTargetAsSR;
std::function<void(std::vector<void*> renderTargets, bool bindDS)> PipelineFunctions::pipeline_bindRenderTargetAsRT;

std::function<void(void*, UINT, BUFFER_TYPE)> PipelineFunctions::pipeline_bindBuffer;
std::function<void(void*)> PipelineFunctions::pipeline_bindInputLayout;

std::function<void(PRIMITIVE_TOPOLOGY)> PipelineFunctions::pipeline_setPrimitiveTopology;

std::function<void(DEPTH_TEST_STATE)> PipelineFunctions::pipeline_set_depth_test_state;
std::function<void(BLEND_STATE)> PipelineFunctions::pipeline_set_blend_state;

std::function<void(RASTER_STATE)> PipelineFunctions::pipeline_set_raster_state;

std::function<void(int,int)> PipelineFunctions::pipeline_drawIndexed;

std::function<void()> PipelineFunctions::pipeline_reset;

std::function<void()> PipelineFunctions::pipeline_clearDepthStencil;

std::function<void()> PipelineFunctions::pipeline_swap_frame;
