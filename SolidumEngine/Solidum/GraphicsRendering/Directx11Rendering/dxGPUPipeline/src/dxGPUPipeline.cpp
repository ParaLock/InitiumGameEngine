#include "../include/dxGPUPipeline.h"




dxGPUPipeline::dxGPUPipeline()
{
	_elementList = new std::map<std::string, GPUPipelineElement*>;
	_generalDataVarToBuffHash = new std::map<std::string, ShaderGeneralDataBuffer*>;
	_opList = new std::list<GPUPipelineOP*>;
}


dxGPUPipeline::~dxGPUPipeline()
{
	delete _elementList;
	delete _generalDataVarToBuffHash;
	delete _opList;
}

void dxGPUPipeline::use()
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	int debugRefPoint = -1;

	std::vector<RenderTarget*> outputList;

	ShaderInputLayout* currentInputLayout = nullptr;

	for (std::map<std::string, GPUPipelineElement*>::iterator itr = 
		_elementList->begin(); itr != _elementList->end(); ++itr)
	{
		GPUPipelineElement *newElement = itr->second;

		newElement->type;
		newElement->parentShader;

		if (newElement->core != nullptr) {

			if (newElement->type == GPUPipelineElementType::SOL_TEXTURE_HOOK) {

				Texture *tex = (Texture*)newElement->core;

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

				TextureSampler *texSampler = (TextureSampler*)newElement->core;
	
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


			if (newElement->type == GPUPipelineElementType::SOL_RENDER_TARGET) {

				RenderTarget *renderTarget = (RenderTarget*)newElement->core;


				if (newElement->isOutput) {
					outputList.push_back(renderTarget);
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

				if (outputList.size() > 0) {

					dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

					ID3D11RenderTargetView **renderTargets = new ID3D11RenderTargetView*[outputList.size()];

					for (size_t i = 0; i < outputList.size(); i++) {

						renderTargets[i] = (ID3D11RenderTargetView*)outputList.at(i)->getParameter("D3D_RENDERTARGET");
					}

					dxCore->dxDevContext->OMSetRenderTargets(outputList.size(), renderTargets, dxCore->depthStencil);

					delete[] renderTargets;
				}
			}

			if (newElement->type == GPUPipelineElementType::SOL_BUFFER_HOOK) {

				GPUBuffer *gpuBuff = (GPUBuffer*)newElement->core;
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

				ShaderGeneralDataBuffer *shaderBuff = (ShaderGeneralDataBuffer*)newElement->core;

				GPUBuffer *gpuBuff = (GPUBuffer*)shaderBuff->getGPUBuffer();
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

				ShaderInputLayout *inputLayout = (ShaderInputLayout*)newElement->core;

				currentInputLayout = inputLayout;

				dxDeviceAccessor::dxEncapsulator->dxDevContext->
					IASetInputLayout((ID3D11InputLayout*)inputLayout->getParameter("D3D_INPUT_LAYOUT"));
			}
		}
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

void dxGPUPipeline::processOp(GPUPipelineOP * op)
{
	if (op->type == GPUPipelineSupportedOP::SOL_CLEAR) {
		if (op->targetType == GPUPipelineElementType::SOL_RENDER_TARGET) {
			RenderTarget *renderTarget = (RenderTarget*)op->pTarget;

			renderTarget->Clear(0,0,0,0);
		}
	}	
}

void dxGPUPipeline::draw(int numIndices)
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
