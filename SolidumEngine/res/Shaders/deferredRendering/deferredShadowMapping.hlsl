#include "shaderUniforms.inc"

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float2 tex : TEXCOORD;
	float4 position : TEXCOORD1;
	float4 worldPos : TEXCOORD2;
	float4 lightViewPosition : TEXCOORD3;
};

Texture2D positionTexture : register(t0);
Texture2D depthBuffer : register(t1);

SamplerState SampleTypePoint : register(s0);

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 worldPos = positionTexture[input.tex];

	output.lightViewPosition = mul(input.position, cbuff_worldMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, cbuff_lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, cbuff_orthoProjection);
	
	output.tex = input.tex;

	return output;
}

float4 Pshader(PixelInputType input) : SV_TARGET
{
	return input.lightViewPosition;
}
	

