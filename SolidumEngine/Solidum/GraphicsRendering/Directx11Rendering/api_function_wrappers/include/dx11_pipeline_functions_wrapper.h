#pragma once

#ifndef DX11_PIPELINE_FUNCTIONS_H
#define DX11_PIPELINE_FUNCTIONS_H

#include "../../../../sysInclude.h"

#include "../../../../ResourceFramework/include/IResource.h"

#include "../../../Textures/include/TextureSampler.h"
#include "../../../../EngineUtils/include/DynamicStruct.h"
#include "../../../../GraphicsRendering/Textures/include/Texture.h"
#include "../../../Shaders/include/ShaderInputLayout.h"
#include "../../../GraphicsBuffers/include/GPUBuffer.h"
#include "../../../RenderTarget/include/RenderTarget.h"

#include "../../../Directx11Rendering/dxDevice/include/dxDeviceAccessor.h"

void dx11_bind_shader_texture_sampler(int bindSlot, SHADER_TYPE parentShader, void* pTexSampler);
void dx11_bind_shader_constant_buffer(int bindSlot, SHADER_TYPE parentShader, void* pConstBuffer);
void dx11_bind_shader_texture(int bindSlot, SHADER_TYPE parentShader, void* pTexture);
void dx11_bind_shader_input_layout(void* pInputLayout);
void dx11_bind_shader_buffer(std::vector<void*> buffers, std::vector<UINT> buffStrides, BUFFER_TYPE buffType);
void dx11_bind_render_target_as_sr(void* rt, SHADER_TYPE parentShader, int bindSlot);
void dx11_bind_render_targets_as_rt(std::vector<void*> renderTargets, void* depthStencil);
void dx11_set_primitive_topology(PRIMITIVE_TOPOLOGY ptType);

void dx11_set_viewport(float maxDepth, float minDepth, int width, int height);

void dx11_set_depth_test_state(DEPTH_TEST_STATE depthTestState);
void dx11_set_blend_state(BLEND_STATE blendState);

void dx11_set_raster_state(RASTER_STATE state);

void dx11_pipeline_draw_indexed(int index, int numIndices);

void dx11_pipeline_swapframe();
void dx11_reset_pipeline();

#endif