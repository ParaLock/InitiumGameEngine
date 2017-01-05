#include "shaderUniforms.inc"

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	return output;
}

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleTypePoint : register(s0);

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;
	float3 lightDir;
	float4 lightIntensity;
	float4 outputColor;
	float4 test;

	colors = colorTexture.Sample(SampleTypePoint, input.tex);
	normals = normalTexture.Sample(SampleTypePoint, input.tex);

	lightDir = normalize(-lightDirection);

	lightIntensity = saturate(dot(normals.xyz, lightDir));

	lightIntensity *= lightColor;

	outputColor = colors;

	outputColor += colors * lightIntensity;

	return outputColor;
}
