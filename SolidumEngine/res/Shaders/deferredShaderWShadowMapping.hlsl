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
	float3 worldPos : TEXCOORD1;
	float4 depthPosition : TEXCOORD2;
	float4 lightViewPosition : TEXCOORD3;
};

Texture2D shadowTexture : register(t4);

SamplerState SampleTypePoint : register(s0);

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 worldPos = positionTexture[input.tex];
	
	output.worldPos = worldPos;
	
	input.position.w = 1.0f;
	
	output.position = mul(output.position, cbuff_worldMatrix);
	output.position = mul(input.position, cbuff_camViewStart);
	output.position = mul(output.position, cbuff_orthoProjection);

	output.lightViewPosition = mul(worldPos, worldMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightViewMatrix);
    output.lightViewPosition = mul(output.lightViewPosition, lightProjectionMatrix);

	//output.depthPosition = worldPos;
	
	output.tex = input.tex;

	return output;
}

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float bias;
	float2 projectTexCoord;
	float lightDepthValue;
	
	bias = 0.001f;
	
	projectTexCoord.x =  input.lightViewPosition.x / input.lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.lightViewPosition.y / input.lightViewPosition.w / 2.0f + 0.5f;
	
	float depthValue = input.depthPosition.z / input.depthPosition.w;

	lightDepthValue = input.lightViewPosition.z / input.lightViewPosition.w;
	lightDepthValue = lightDepthValue - bias;
	
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		if(lightDepthValue < depthValue)
		{
			//NOT SHADOWED
		}
	}
}
	

