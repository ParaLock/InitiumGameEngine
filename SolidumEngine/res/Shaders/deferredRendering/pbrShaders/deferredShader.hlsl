#include "shaderUniforms.inc"

struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float4 worldPos : TEXCOORD1;
	float2 texCoords : TEXCOORD;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
	float4 position : SV_Target2;
};

Texture2D model_tex : register(t0);

Texture2D specularTexture : register(t3);

Texture2D pbr_colorTexture : register(t4);
Texture2D pbr_emessiveTexture : register(t5);
Texture2D pbr_roughnessTexture : register(t6);
Texture2D pbr_normalTexture : register(t7);

SamplerState SampleTypeWrap : register(s0);

void CreateGBufferMaterial(PixelInputType input, inout MaterialData mat) {

	mat.diffuseColor = pbr_colorTexture.Sample(SampleTypeWrap, );
}

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
	
	return output;
}

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;
	
	MaterialData mat;
	
	CreateGBufferMaterial(mat);
	
	float4 ambientLight = { 0.05f, 0.05f, 0.05f, 0.05f };
		
	float4 texColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	
	
	return output;
}