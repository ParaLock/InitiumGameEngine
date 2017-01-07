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
	float3 worldPos : POSITION0;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD0;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
};


PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	matrix FinalworldMatrix = mul(OBJSpecificMatrix, worldMatrix);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, FinalworldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = normalize(mul(input.normal, (float3x3)FinalworldMatrix));
	
	output.worldPos = mul(input.position, worldMatrix);
	
	return output;
}

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float3 V = normalize(eyePos - input.worldPos);
	
	float3 R = reflect( normalize( lightDirection ), normalize( input.normal ) );
	
	//float diffuseFactor = dot(input.normal, -lightDirection);
	
	//float4 specularColor = float4(0,0,0,0);
	
	float4 texColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	
	//if(diffuseFactor > 0) {
	//
	//	float3 directionToEye = normalize(eyePos - input.worldPos);
	//	float3 reflectDirection = normalize(reflect(lightDirection, input.normal));
	//
	//	float specularFactor = dot(directionToEye, reflectDirection);
	//
	//	specularFactor = pow(specularFactor, specularPower);
	//
	//	if(specularFactor > 0) 
	//	{
	//		specularColor = lightColor * specularPower * specularFactor;
	//	}
	//
	//}

	output.normal = float4(input.normal, 1.0f);
	output.color = specularShininess * lightColor * pow( saturate( dot( R, V ) ), specularPower );
	
	return output;
}