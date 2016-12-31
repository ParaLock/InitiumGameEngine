#include "../include/dxTextureSampleState.h"



dxTextureSampleState::dxTextureSampleState(TEX_FILTERS texFilterType, ANISOTRPHIC_FILTER_LEVELS anisotropyFilterLevel, TEX_ADDR_MODES texAddressMode)
{
	ID3D11Device *dxDev = dxDeviceAccessor::dxEncapsulator->dxDev;

	D3D11_SAMPLER_DESC samplerStateDesc;

	ZeroMemory(&samplerStateDesc, sizeof(samplerStateDesc));

	switch (texFilterType) {
	case TEX_FILTER_ANISOTROPHIC:
		samplerStateDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		break;
	case TEX_FILTER_LINEAR:
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		break;
	case TEX_FILTER_POINT:
		samplerStateDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		break;
	default:
		break;
	}

	switch (texAddressMode) {
	case TEX_ADDR_MODE_WRAP:
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		break;
	case TEX_ADDR_MODE_CLAMP:
		samplerStateDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerStateDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerStateDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		break;
	default:
		break;
	}

	switch (anisotropyFilterLevel) {
	case HIGHEST_QUALITY:
		samplerStateDesc.MaxAnisotropy = 16;
		break;
	case HIGH_QUALITY:
		samplerStateDesc.MaxAnisotropy = 8;
		break;
	case MEDIUM_QUALITY:
		samplerStateDesc.MaxAnisotropy = 4;
		break;
	case NO_ANISOTROPHIC_FILTERING:
		samplerStateDesc.MaxAnisotropy = 1;
		break;
	default:
		samplerStateDesc.MaxAnisotropy = 1;
		break;
	}

	samplerStateDesc.MipLODBias = 0.0f;
	samplerStateDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerStateDesc.MinLOD = 0;
	samplerStateDesc.MaxLOD = D3D11_FLOAT32_MAX;

	dxDev->CreateSamplerState(&samplerStateDesc, &sampleState);
}


dxTextureSampleState::~dxTextureSampleState()
{
	sampleState->Release();
}

void dxTextureSampleState::updateParameter(std::string varName, void * data)
{
	if (varName == "D3D_TEXTURESAMPLER") {
		sampleState = (ID3D11SamplerState*)data;
	}
}

void * dxTextureSampleState::getParameter(std::string varName)
{
	if (varName == "D3D_TEXTURESAMPLER") {
		return sampleState;
	}

	return nullptr;
}

