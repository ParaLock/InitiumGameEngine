#include "../include/dxShader.h"

dxShader::dxShader(LPCWSTR shaderFilename, LPCWSTR pipelineDescFilename)
{

	_pipelineState = GPUPipelineFactory::createPipeline(pipelineDescFilename);

	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	D3DX11CompileFromFile(shaderFilename, 0, 0, "Vshader", "vs_5_0", 0, 0, 0, &vertexShaderCode, 0, 0);
	dxDev->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);

	D3DX11CompileFromFile(shaderFilename, 0, 0, "Pshader", "ps_5_0", 0, 0, 0, &pixelShaderCode, 0, 0);
	dxDev->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
}


dxShader::~dxShader()
{
}

void dxShader::performRenderPass(int numIndices)
{
	dxDeviceAccessor::dxEncapsulator->dxDevContext->VSSetShader(vertexShader, NULL, 0);
	dxDeviceAccessor::dxEncapsulator->dxDevContext->PSSetShader(pixelShader, NULL, 0);

	_pipelineState->use();

	_pipelineState->draw(numIndices);
}

void dxShader::updateGPU()
{

}
