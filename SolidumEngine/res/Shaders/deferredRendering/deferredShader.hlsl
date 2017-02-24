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
	float4 depthPosition : TEXCOORD2;
	float4 lightViewPosition : TEXCOORD3;
	float4 worldPos : TEXCOORD1;
	float2 tex : TEXCOORD;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
	float4 position : SV_Target2;
	float4 specularColor : SV_Target3;
	float4 shadowMap : SV_Target4;
};


PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	input.position.w = 1.0f;

	matrix FinalworldMatrix = mul(cbuff_OBJSpecificMatrix, cbuff_worldMatrix);

	output.position = mul(input.position, FinalworldMatrix);
	
	output.worldPos = output.position;
	
	output.position = mul(output.position, cbuff_viewMatrix);
	output.position = mul(output.position, cbuff_projectionMatrix);
	
	output.lightViewPosition = mul(input.position, FinalworldMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, cbuff_lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, cbuff_lightProjectionMatrix);
	
	output.depthPosition = output.position;
	
	output.tex = input.tex;

	output.normal = mul(input.normal, FinalworldMatrix);
	
	return output;
}

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float4 ambientLight = { 0.05f, 0.05f, 0.05f, 0.05f };
		
	float4 texColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	float depthValue = input.depthPosition.z / input.depthPosition.w;
	
	output.shadowMap.xyz = input.lightViewPosition.xyz;
	
	output.shadowMap.w = depthValue;
	
	output.color = texColor; 
	
	output.normal.xyz = input.normal.xyz;
	output.normal.w = cbuff_specularIntensity;
	
	output.position.xyz = input.worldPos.xyz;
	
	output.position.w = cbuff_specularPower;
	
	output.specularColor = cbuff_specularColor;

	
	return output;
}