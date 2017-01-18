#include "../include/dxGPUPipeline.h"




dxGPUPipeline::dxGPUPipeline(ResourceManagerPool* managerPool)
{
	_resManagerPool = managerPool;
}


dxGPUPipeline::~dxGPUPipeline()
{
}

void dxGPUPipeline::applyState()
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int debugRefPoint = -1;

	std::vector<RenderTarget*> outputRTList;

	ShaderInputLayout* currentInputLayout;

	ID3D11ShaderResourceView* nullSRV[9] = { nullptr };
	ID3D11RenderTargetView* nullTV[9] = { nullptr };
	ID3D11DepthStencilView* nullDS = { nullptr };

	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(0, 8, nullSRV);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(0, 8, nullSRV);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->OMSetRenderTargets(8, nullTV, nullDS);

	for (std::map<std::string, GPUPipelineElement*>::iterator itr =
		_elementList->begin(); itr != _elementList->end(); ++itr)
	{
		GPUPipelineElement* newElement = itr->second;

		newElement->name;
		newElement->type;
		newElement->parentShader;

		if (newElement->core != nullptr) {

			if (newElement->type == GPUPipelineElementType::SOL_RENDER_TARGET) {

				RenderTarget* renderTarget = newElement->core->getCore<RenderTarget>();

				if (newElement->isOutput) {
					outputRTList.push_back(renderTarget);
				}
				else {

					ID3D11ShaderResourceView* tmpRT = (ID3D11ShaderResourceView*)renderTarget->getParameter("D3D_SHADERVIEW");

					if (newElement->parentShader == GPUPipelineElementParentShader::SOL_PS) {

						dxDeviceAccessor::dxEncapsulator->dxDevContext->
							PSSetShaderResources(newElement->resourceSlot, 1,
								&tmpRT);
					}
					else if (newElement->parentShader == GPUPipelineElementParentShader::SOL_VS) {
						dxDeviceAccessor::dxEncapsulator->dxDevContext->
							VSSetShaderResources(newElement->resourceSlot, 1,
								&tmpRT);
					}
				}
			}

			if (newElement->type == GPUPipelineElementType::SOL_TEXTURE_HOOK) {

				Texture* tex = newElement->core->getCore<Texture>();

				ID3D11ShaderResourceView* dxTex =
					(ID3D11ShaderResourceView*)tex->getParameter("D3D_TEXTURE");

				if (newElement->parentShader == GPUPipelineElementParentShader::SOL_PS) {
					dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShaderResources(newElement->resourceSlot, 1,
						&dxTex);
				}
				else if (newElement->parentShader == GPUPipelineElementParentShader::SOL_VS) {
					dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShaderResources(newElement->resourceSlot, 1,
						&dxTex);
				}
			}

			if (newElement->type == GPUPipelineElementType::SOL_SAMPLER) {

				TextureSampler* texSampler = newElement->core->getCore<TextureSampler>();

				ID3D11SamplerState* dxTexSampler =
					(ID3D11SamplerState*)texSampler->getParameter("D3D_TEXTURESAMPLER");

				if (newElement->parentShader == GPUPipelineElementParentShader::SOL_PS) {
					dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetSamplers(newElement->resourceSlot, 1,
						&dxTexSampler);
				}
				else if (newElement->parentShader == GPUPipelineElementParentShader::SOL_VS) {
					dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetSamplers(newElement->resourceSlot, 1,
						&dxTexSampler);
				}
			}


			if (newElement->type == GPUPipelineElementType::SOL_BUFFER_HOOK) {

				GPUBuffer* gpuBuff = newElement->core->getCore<GPUBuffer>();

				ID3D11Buffer *gpuBuffPtr = (ID3D11Buffer*)gpuBuff->getParameter("D3D_BUFFER");

				if (gpuBuff->getBuffType() == BUFFER_TYPE::INDEX_BUFF) {

					dxDeviceAccessor::dxEncapsulator->dxDevContext->
						IASetIndexBuffer(gpuBuffPtr, DXGI_FORMAT_R32_UINT, 0);
				}
				if (gpuBuff->getBuffType() == BUFFER_TYPE::VERTEX_BUFF) {

					if (currentInputLayout != nullptr) {

						UINT offset = 0;
						UINT stride = currentInputLayout->getDataStride();

						dxDeviceAccessor::dxEncapsulator->dxDevContext->
							IASetVertexBuffers(0, 1, &gpuBuffPtr, &stride, &offset);
					}
				}
			}


			if (newElement->type == GPUPipelineElementType::SOL_GENERAL_DATA_BUFF) {

				DynamicBuffer* shaderBuff = newElement->core->getCore<DynamicBuffer>();

				GPUBuffer* gpuBuff = shaderBuff->getGPUBuffer();

				ID3D11Buffer *gpuBuffPtr = (ID3D11Buffer*)gpuBuff->getParameter("D3D_BUFFER");

				if (gpuBuff->getBuffType() == BUFFER_TYPE::SHADER_BUFF) {
					if (newElement->parentShader == GPUPipelineElementParentShader::SOL_VS) {
						dxDeviceAccessor::dxEncapsulator->dxDevContext->
							VSSetConstantBuffers(newElement->resourceSlot, 1, &gpuBuffPtr);
					}
					if (newElement->parentShader == GPUPipelineElementParentShader::SOL_PS) {
						dxDeviceAccessor::dxEncapsulator->dxDevContext->
							PSSetConstantBuffers(newElement->resourceSlot, 1, &gpuBuffPtr);
					}
				}
			}

			if (newElement->type == GPUPipelineElementType::SOL_MESH_DATA_LAYOUT) {

				ShaderInputLayout* inputLayout = newElement->core->getCore<ShaderInputLayout>();

				currentInputLayout = inputLayout;

				dxDeviceAccessor::dxEncapsulator->dxDevContext->
					IASetInputLayout((ID3D11InputLayout*)inputLayout->getParameter("D3D_INPUT_LAYOUT"));
			}

		}

	}

	if (outputRTList.size() > 0) {

		dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

		ID3D11RenderTargetView **renderTargets = new ID3D11RenderTargetView*[outputRTList.size()];

		for (size_t i = 0; i < outputRTList.size(); i++) {

			renderTargets[i] = (ID3D11RenderTargetView*)outputRTList.at(i)->getParameter("D3D_RENDERTARGET");
		}

		dxCore->dxDevContext->OMSetRenderTargets(outputRTList.size(), renderTargets, dxCore->depthStencil);

		delete[] renderTargets;
	}

	if (depthTestEnabled) {
		dxDeviceAccessor::dxEncapsulator->enableDepthStencil();
	}
	else {
		dxDeviceAccessor::dxEncapsulator->disableDepthStencil();
	}

	if (blendingEnabled) {
		dxDeviceAccessor::dxEncapsulator->enableBlending();
	}
	else {
		dxDeviceAccessor::dxEncapsulator->disableBlending();
	}

}

void dxGPUPipeline::processOp(GPUPipelineOP* op)
{
	if (op->type == GPUPipelineSupportedOP::SOL_CLEAR) {
		if (op->targetType == GPUPipelineElementType::SOL_RENDER_TARGET) {

			RenderTarget* renderTarget = _resManagerPool
				->getResourceManager("RenderTargetManager")->getResource(op->targetName)->getCore<RenderTarget>();

			renderTarget->Clear(0,0,0,0);

		}
		if (op->targetType == GPUPipelineElementType::SOL_ZBUFFER) {
			dxDeviceAccessor::dxEncapsulator->clearDepthStencil();
		}
	}

	if (op->type == GPUPipelineSupportedOP::SOL_SWAPFRAME) {
		dxDeviceAccessor::dxEncapsulator->dxSwapchain->Present(1, 0);
	}
}

void dxGPUPipeline::executePass(int numIndices)
{
	std::list<GPUPipelineOP*> deferredOps;

	for (std::list<GPUPipelineOP*>::iterator itr = _opList->begin(); itr != _opList->end(); itr++) {
		GPUPipelineOP* op = *itr;
		if (!op->deferred) {
			processOp(op);
		}
		else {
			deferredOps.push_back(op);
		}
	}

	dxDeviceAccessor::dxEncapsulator->dxDevContext->DrawIndexed(numIndices, 0, 0);

	for (std::list<GPUPipelineOP*>::iterator itr = deferredOps.begin(); itr != deferredOps.end(); itr++) {
		processOp(*itr);
	}
}
