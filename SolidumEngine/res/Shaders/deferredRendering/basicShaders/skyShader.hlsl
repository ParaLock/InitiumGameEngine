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
	float4 apexColor : APEX_COLOR;
	float4 centerColor : CENTER_COLOR;
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
	
	output.apexColor = cbuff_skydomeApexColor;
	output.centerColor = cbuff_skydomeCenterColor;
	
	return output;
}

TextureCube skyCube : register(t0);

SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	float height;
	PixelOutputType output;

	height = input.PosL.y;

	if(height < 0.0)
	{
		height = 0.0f;
	}
	
	output.color = skyCube.Sample(SampleTypeWrap, input.PosL);
	
	output.color *= lerp(input.centerColor, input.apexColor, height);
	
	return output;
}