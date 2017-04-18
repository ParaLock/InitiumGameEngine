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
	
	depthValue = 1-(input.depthPosition.z / input.depthPosition.w);

	//depthValue = depthValue * 0.5 + 0.5;	
	
	float moment1 = depthValue;
	float moment2 = depthValue * depthValue;
	
	float dx = ddx(depthValue);
	float dy = ddy(depthValue);
	moment2 += 0.25*(dx*dx+dy*dy);
	
	output.depth = float4(moment1,moment2, 0.0, 0.0);
	
	return output;
}
