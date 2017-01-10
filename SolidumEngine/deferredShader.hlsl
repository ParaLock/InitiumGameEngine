#include "shaderUniforms.inc"

struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 worldPos : TEXCOORD1;
	float2 tex : TEXCOORD;
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

	input.position.w = 1.0f;

	matrix FinalworldMatrix = mul(OBJSpecificMatrix, worldMatrix);

	output.worldPos.xyz = normalize(mul(input.position, worldMatrix)).xyz;
	
	output.position = mul(input.position, FinalworldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.tex = input.tex;

	output.normal = normalize(mul(input.normal, worldMatrix));
	
	return output;
}

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float4 ambientLight = { 0.2f, 0.2f, 0.2f, 0.2f };
		
	float4 texColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	output.color.xyz = texColor.xyz; 
	output.color.w = materialID;
	
	output.normal.xyz = input.normal.xyz;
	output.normal.w = specularIntensity;
	
	output.position.xyz = input.worldPos.xyz;
	output.position.w = specularPower;
	
	output.specularColor = specularColor;
	
	return output;
}