#include "shaderUniforms.inc"

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
	
	float2   texOffset1 : V_TEX_OFFSETONE;
	float2   texOffset2 : V_TEX_OFFSETTWO;
	float2   texCoordInfo : V_TEX_INFO;
	float4x4 instanceMatrix : V_MATRIX;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	
	float2   texCoords1 : P_TEX_COORD1;
	float2   texCoords2 : P_TEX_COORD2;
	
	float 	 blend : P_TEX_COORD_BLEND;
};

struct PixelOutputType
{
	float4 color : !% PIXEL_SHADER gbuff_colors !%
};

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 pos = float4(input.position, 1.0f);
	
	pos.w = 1.0f;
	
	float2 textureCoordinates = pos + float2(0.5f, 0.5f);
	
	textureCoordinates.y = 1.0 - textureCoordinates.y;
	textureCoordinates /= input.texCoordInfo.x;

	output.texCoords1 = textureCoordinates + input.texOffset1;
	output.texCoords2 = textureCoordinates + input.texOffset2;
	
	output.blend = input.texCoordInfo.y;
	
	output.position = mul(pos, input.instanceMatrix);
	output.position = mul(output.position, cbuff_projectionMatrix);
	
	return output;
}

Texture2D colorTexture : !% PIXEL_SHADER particle_texture !%

SamplerState SampleTypeWrap : !% PIXEL_SHADER SampleTypeWrap !%
SamplerState SampleTypePoint : !% PIXEL_SHADER SampleTypePoint!%

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;
	
	float4 color1 = colorTexture.Sample(SampleTypePoint, input.texCoords1);
	float4 color2 = colorTexture.Sample(SampleTypePoint, input.texCoords2);
	
	output.color = lerp(color1, color2, input.blend);
	
	return output;
}