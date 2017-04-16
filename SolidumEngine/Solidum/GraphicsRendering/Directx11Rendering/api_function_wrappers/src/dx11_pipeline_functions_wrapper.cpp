#include "../include/dx11_pipeline_functions_wrapper.h"

void dx11_bind_shader_texture_sampler(int bindSlot, SHADER_TYPE parentShader, void* pTexSampler) {

	ID3D11SamplerState* dxTexSampler = (ID3D11SamplerState*)pTexSampler;

	if (parentShader == SHADER_TYPE::PIXEL_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetSamplers(bindSlot, 1,
			&dxTexSampler);
	}

	if (parentShader == SHADER_TYPE::VERTEX_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetSamplers(bindSlot, 1,
			&dxTexSampler);
	}
}

void dx11_bind_shader_constant_buffer(int bindSlot, SHADER_TYPE parentShader, void* pConstBuffer) {

	ID3D11Buffer *gpuBuffPtr = (ID3D11Buffer*)pConstBuffer; 

	if (parentShader == SHADER_TYPE::VERTEX_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			VSSetConstantBuffers(bindSlot, 1, &gpuBuffPtr);
	}
	if (parentShader == SHADER_TYPE::PIXEL_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			PSSetConstantBuffers(bindSlot, 1, &gpuBuffPtr);
	}
}

void dx11_bind_shader_texture(int bindSlot, SHADER_TYPE parentShader, void* pTexture) {

	ID3D11ShaderResourceView* pTex = (ID3D11ShaderResourceView*)pTexture;

	if (parentShader == SHADER_TYPE::PIXEL_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(bindSlot, 1,
			&pTex);
	}
	else if (parentShader == SHADER_TYPE::VERTEX_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(bindSlot, 1,
			&pTex);
	}
}

void dx11_bind_shader_input_layout(void* pInputLayout) {

	dxDeviceAccessor::dxEncapsulator->dxDevContext->
		IASetInputLayout((ID3D11InputLayout*)pInputLayout);
}

void dx11_bind_shader_buffer(void* buffer, UINT buffStride, BUFFER_TYPE buffType) {

	ID3D11Buffer *gpuBuffPtr = (ID3D11Buffer*)buffer;

	if (buffType == BUFFER_TYPE::INDEX_BUFF) {

		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			IASetIndexBuffer(gpuBuffPtr, DXGI_FORMAT_R32_UINT, 0);
	}
	if (buffType == BUFFER_TYPE::VERTEX_BUFF) {

		UINT offset = 0;
		UINT stride = buffStride;

		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			IASetVertexBuffers(0, 1, &gpuBuffPtr, &stride, &offset);

	}
}

void dx11_bind_render_target_as_sr(void* rt, SHADER_TYPE parentShader, int bindSlot) {

	ID3D11ShaderResourceView* pRt = (ID3D11ShaderResourceView*)rt;

	if (parentShader == SHADER_TYPE::PIXEL_SHADER) {

		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			PSSetShaderResources(bindSlot, 1,
				&pRt);
	}
	else if (parentShader == SHADER_TYPE::VERTEX_SHADER) {
		dxDeviceAccessor::dxEncapsulator->dxDevContext->
			VSSetShaderResources(bindSlot, 1,
				&pRt);
	}
}

void dx11_bind_render_targets_as_rt(std::vector<void*> renderTargets, void* depthStencil) {

	ID3D11RenderTargetView **dxRenderTargets = new ID3D11RenderTargetView*[renderTargets.size()];

	for (size_t i = 0; i < renderTargets.size(); i++) {

		dxRenderTargets[i] = (ID3D11RenderTargetView*)renderTargets.at(i);
	}

	dxDeviceAccessor::dxEncapsulator->dxDevContext->OMSetRenderTargets(renderTargets.size(),
		dxRenderTargets, (ID3D11DepthStencilView*)depthStencil);
	

	delete[] dxRenderTargets;
}

void dx11_set_primitive_topology(PRIMITIVE_TOPOLOGY ptType) {

	switch (ptType)
	{
	case PRIMITIVE_TOPOLOGY::TRANGLE_LIST:

		dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	default:
		break;
	}
}

void dx11_set_viewport(float maxDepth, float minDepth, int width, int height)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(viewport));

	viewport.Width = width;
	viewport.Height = height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MaxDepth = maxDepth;
	viewport.MinDepth = minDepth;

	dxDeviceAccessor::dxEncapsulator->dxDevContext->RSSetViewports(1, &viewport);
}

void dx11_reset_pipeline() {

	ID3D11ShaderResourceView* nullSRV[9] = { nullptr };
	ID3D11RenderTargetView* nullTV[9] = { nullptr };
	ID3D11DepthStencilView* nullDS = { nullptr };

	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(0, 8, nullSRV);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(0, 8, nullSRV);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->OMSetRenderTargets(8, nullTV, nullDS);
}

void dx11_set_depth_test_state(DEPTH_TEST_STATE depthTestState) {
	dxDeviceAccessor::dxEncapsulator->setDepthTestState(depthTestState);
}

void dx11_set_blend_state(BLEND_STATE blendState) {
	dxDeviceAccessor::dxEncapsulator->setBlendState(blendState);
}

void dx11_set_raster_state(RASTER_STATE state)
{
	dxDeviceAccessor::dxEncapsulator->setRasterState(state);
}

void dx11_pipeline_draw_indexed(int index, int numIndices)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->DrawIndexed(numIndices, index, 0);
}

void dx11_pipeline_swapframe() {
	dxDeviceAccessor::dxEncapsulator->dxSwapchain->Present(1, 0);
}
