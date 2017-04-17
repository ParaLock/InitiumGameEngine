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
    float4 depthPosition : TEXTURE0;
};

struct PixelOutputType
{
	float4 depth : SV_Target0;
};

PixelInputType Vshader(VertexInputType input)
{
    PixelInputType output;
    
    input.position.w = 1.0f;
	
	matrix WMMatrix = mul(cbuff_OBJSpecificMatrix, cbuff_worldMatrix);
	
	output.position = mul(input.position, WMMatrix);
	output.position = mul(output.position, cbuff_lightDepthView);
	output.position = mul(output.position, cbuff_lightDepthProjection);
	
	output.depthPosition = output.position;
	
	return output;
}

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float depthValue;
	float4 color;
	
	depthValue = input.depthPosition.z / input.depthPosition.w;

	output.depth = float4(depthValue, depthValue, depthValue, 1.0f);
	
	return output;
}
