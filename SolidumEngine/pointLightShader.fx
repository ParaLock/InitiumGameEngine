cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightBuffer
{
	float3 lightDirection;
	float padding1;
	float3 lightPos;
	float padding2;
	float4 ambientColor;
	float4 lightColor;
	float3 eyeView;
	float padding5;
};

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
	float4 outputColor;

	colors = colorTexture.Sample(SampleTypePoint, input.tex);
	normals = normalTexture.Sample(SampleTypePoint, input.tex);

	float3 lightDir = normalize(lightPos - (float3)input.position);

	float diffuseLighting = saturate(dot(normals, -lightDir));
								
	diffuseLighting *= ((length(lightDir) * length(lightDir)) / dot(lightPos - (float3)input.position, lightPos - (float3)input.position));

	float3 h = normalize(normalize(eyeView - (float3)input.position) - lightDir);

	outputColor = saturate(ambientColor + (lightColor * diffuseLighting * 0.6f));

	return outputColor;
}