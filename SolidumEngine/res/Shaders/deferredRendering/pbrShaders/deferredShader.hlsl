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
	float4 glow : SV_Target2;
};

Texture2D colorTexture : register(t0);

Texture2D mat_tex_albedo : register(t1);
Texture2D mat_tex_normal : register(t2);
Texture2D mat_tex_specular : register(t3);

Texture2D mat_tex_pbr_emessive : register(t4);
Texture2D mat_tex_pbr_roughness : register(t5);

SamplerState SampleTypeWrap : register(s0);

void CreateMaterial(PixelInputType input, inout materialData mat)
{
	mat.diffuseColor = mat_tex_albedo.Sample(SampleTypeWrap, input.tex) 
                                              * float4(colorTexture.Sample(SampleTypeWrap, input.tex), 1.0f);
											  
	float4 bumpNormal = mat_tex_normal.Load(int3(input.position.xy, 0));
        
	float4 emessiveColor = mat_tex_pbr_emessive.Sample(SampleTypeWrap, input.tex) 
                                                  * float4(float3(0.2f, 0.2f, 0.2f), 1.0f);

	mat.glowColor = emessiveColor.rgb;

	mat.glowIntensity = 0.5f;

	bumpNormal = (bumpNormal  * 2.0f) - 1.0f;

	mat.normal = (bumpNormal.x * input.tangent) 
            + (bumpNormal.y * input.binormal) + (bumpNormal.z * input.normal);

	mat.normal = normalize(input.normal);

	mat.roughness = mat_tex_pbr_roughness.Sample(SampleTypeWrap, input.tex).r; * 0.5f;
	mat.metallic = mat_tex_pbr_roughness.Sample(SampleTypeWrap, input.tex).r;
 
	mat.roughness *= 0.5f;
	mat.metallic *= 0.5f;
}

void PackOutput(inout PixelOutputType output, MaterialData mat)
{
    output.color = float4(mat.diffuseColor.rgb, mat.roughness);

    output.normal = float4(mat.normal.xyz, mat.metallic);

	output.glow = float4(mat.glowColor * mat.glowIntensity, 1.0f);
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

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;
	
	MaterialData mat;
	
	CreateMaterial(input, mat);
	
	PackOutput(output, mat);
	
	return output;
}