#include "shaderUniforms.inc"

struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 worldPos : TEXCOORD0;
	float2 tex : TEXCOORD1;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
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

	matrix FinalworldMatrix = mul(cbuff_OBJSpecificMatrix, cbuff_worldMatrix);

	output.position = mul(input.position, FinalworldMatrix);
	
	output.worldPos = output.position;
	
	output.position = mul(output.position, cbuff_viewMatrix);
	output.position = mul(output.position, cbuff_projectionMatrix);
	
	output.tex = input.tex;

	output.normal = mul(input.normal, FinalworldMatrix);
	
	output.tangent = mul(input.tangent, cbuff_projectionMatrix);
	output.binormal = mul(input.binormal, cbuff_projectionMatrix);
	
	return output;
}

Texture2D colorTexture : register(t0);

Texture2D mat_tex_albedo : register(t1);
Texture2D mat_tex_normal : register(t2);
Texture2D mat_tex_specular : register(t3);

Texture2D mat_tex_pbr_emessive : register(t4);
Texture2D mat_tex_pbr_roughness : register(t5);

SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float4 ambientLight = { 0.05f, 0.05f, 0.05f, 0.05f };
		
	float4 texColor = colorTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	output.color = texColor; 
	
	output.normal.xyz = input.normal;
	output.normal.w = cbuff_specularIntensity;
	
	output.position.xyz = input.worldPos.xyz;
	
	output.position.w = cbuff_specularPower;
	
	output.specularColor = cbuff_specularColor;

	return output;
}