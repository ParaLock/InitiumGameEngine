#include "shaderUniforms.inc"

struct VertexInputType
{
	float3 PosL : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
};

struct PixelInputType
{
	float4 PosH : SV_POSITION;
    float3 PosL : POSITION;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
	float4 position : SV_Target2;
	float4 specularColor : SV_Target3;
};

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;
	
	output.PosH = mul(float4(input.PosL, 1.0f), cbuff_skydomeWorldViewProj);
	
	output.PosL = input.PosL;
	
	return output;
}

TextureCube skyCube : register(t0);

SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	output.color = skyCube.Sample(SampleTypeWrap, input.PosL);
	
	return output;
}