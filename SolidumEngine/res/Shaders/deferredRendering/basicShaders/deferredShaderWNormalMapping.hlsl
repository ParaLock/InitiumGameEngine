#include "shaderUniforms.inc"

struct VertexInputType
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 worldPos : WORLDPOS;
	float2 tex : TEXCOORD;
	float3 binormal : BINORMAL;
	float3 tangent : TANGENT;
};

struct PixelOutputType
{
	float4 color : !% PIXEL_SHADER gbuff_colors !%
	float4 normal : !% PIXEL_SHADER gbuff_normals !%
	float4 position : !% PIXEL_SHADER gbuff_positions !%
	float4 specularColor : !% PIXEL_SHADER gbuff_specular !%
};


PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 pos = float4(input.position, 1);
	
	pos.w = 1.0f;
	
	matrix FinalworldMatrix = mul(cbuff_OBJSpecificMatrix, cbuff_worldMatrix);

	output.position = mul(pos, FinalworldMatrix);
	
	output.worldPos = output.position;
	
	output.position = mul(output.position, cbuff_viewMatrix);
	output.position = mul(output.position, cbuff_projectionMatrix);
	
	output.tex = input.tex;

	output.normal = mul(input.normal, FinalworldMatrix);
	
	output.tangent = mul(input.tangent, cbuff_projectionMatrix);
	output.binormal = mul(input.binormal, cbuff_projectionMatrix);
	
	return output;
}

Texture2D colorTexture : !% PIXEL_SHADER color_texture !%

Texture2D mat_tex_albedo : !% PIXEL_SHADER mat_tex_albedo !%
Texture2D mat_tex_normal : !% PIXEL_SHADER mat_tex_normal !%
Texture2D mat_tex_specular : !% PIXEL_SHADER mat_tex_specular !%

Texture2D mat_tex_pbr_emessive : !% PIXEL_SHADER mat_tex_pbr_emessive !%
Texture2D mat_tex_pbr_roughness : !% PIXEL_SHADER mat_tex_pbr_roughness !%

SamplerState SampleTypeWrap : !% PIXEL_SHADER SampleTypeWrap !%
SamplerState SampleTypePoint : !% PIXEL_SHADER SampleTypePoint!%

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float4 bumpMap;
    float3 bumpNormal;
	
	float4 ambientLight = { 0.05f, 0.05f, 0.05f, 0.05f };
		
	float4 texColor = colorTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	output.color = texColor; 
	
	bumpMap = mat_tex_normal.Sample(SampleTypeWrap, input.tex);
	
	bumpMap = (bumpMap * 2.0f) - 1.0f;
	
	bumpNormal = (bumpMap.x * input.tangent) + (bumpMap.y * input.binormal) + (bumpMap.z * input.normal);
	
	bumpNormal = normalize(bumpNormal);
	
	output.normal.xyz = bumpNormal;
	output.normal.w = cbuff_specularIntensity;
	
	output.position.xyz = input.worldPos.xyz;
	
	output.position.w = cbuff_specularPower;
	
	output.specularColor = cbuff_specularColor;

	return output;
}