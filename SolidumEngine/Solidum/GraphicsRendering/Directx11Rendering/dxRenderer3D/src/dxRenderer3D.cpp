#include "../include/dxRenderer3D.h"



dxRenderer3D::dxRenderer3D()
{
	gBuffers = new std::vector<IRenderTarget*>;
}


dxRenderer3D::~dxRenderer3D()
{
	gBuffers->clear();
	delete gBuffers;
}

void dxRenderer3D::RenderLight(Light * light)
{
	dxDeviceAccessor::dxEncapsulator->disableDepthStencil();
	setFrameBufferAsCurrent();
	dxDeviceAccessor::dxEncapsulator->setViewport("light");

	light->draw();

	setGBuffers("read_stage");

	dxDeviceAccessor::dxEncapsulator->enableBlending();

	dxDeviceAccessor::dxEncapsulator->setLightMesh();

	dxDeviceAccessor::dxEncapsulator->dxDevContext->DrawIndexed(6, 0, 0);

	dxDeviceAccessor::dxEncapsulator->disableBlending();
}

void dxRenderer3D::RenderMesh(mesh * mesh, IShader * shader)
{

	dxDeviceAccessor::dxEncapsulator->dxDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	dxDeviceAccessor::dxEncapsulator->setViewport("mesh");
	dxDeviceAccessor::dxEncapsulator->enableDepthStencil();	

	shader->Bind();

	setGBuffers("write_stage");

	mesh->draw();

	dxDeviceAccessor::dxEncapsulator->dxDevContext->DrawIndexed(mesh->numIndices, 0, 0);
}

void dxRenderer3D::addGBuffer(IRenderTarget * gBuff)
{
	gBuffers->push_back(gBuff);
}

void dxRenderer3D::clearGBuffers(float R, float G, float B, float A)
{
	for (size_t i = 0; i < gBuffers->size(); i++) {
		gBuffers->at(i)->Clear(R, G, B, A);
	}
}

void dxRenderer3D::setGBuffers(std::string gBuffUsageContext)
{
	if (gBuffUsageContext == "write_stage") {

		dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

		ID3D11RenderTargetView **renderTargets = new ID3D11RenderTargetView*[gBuffers->size()];

		for (size_t i = 0; i < gBuffers->size(); i++) {

			dxRenderTarget* tmpRenderTarget = static_cast<dxRenderTarget*>(gBuffers->at(i));

			renderTargets[i] = tmpRenderTarget->GetRenderTarget();
		}

		dxCore->dxDevContext->OMSetRenderTargets(gBuffers->size(), renderTargets, dxCore->depthStencil);

		delete[] renderTargets;
	}

	if (gBuffUsageContext == "read_stage") {
		for (size_t i = 0; i < gBuffers->size(); i++) {

			IRenderTarget *gBuff = gBuffers->at(i);

			gBuff->BindAsShaderResource();
		}
	}
}

void dxRenderer3D::setFrameBufferAsCurrent()
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxDevContext->OMSetRenderTargets(1, &dxCore->FrameBufferShaderAccess, dxCore->depthStencil);
}

void dxRenderer3D::clearFrameBuffer(float R, float G, float B, float A)
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxDevContext->ClearRenderTargetView(dxCore->FrameBufferShaderAccess, D3DXCOLOR(R, G, B, A));
}

void dxRenderer3D::clearZBuffer()
{
	dxDeviceAccessor::dxEncapsulator->clearDepthStencil();
}

void dxRenderer3D::swapFrame()
{
	dxDevice* dxCore = dxDeviceAccessor::dxEncapsulator;

	dxCore->dxSwapchain->Present(1, 0);
}
