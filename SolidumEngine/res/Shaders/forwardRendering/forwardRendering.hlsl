#include "forwardLighting.hlsl"


struct VertexInputType
{
    float4 position : POSITION;
	float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
	float3 normal : NORMAL;
    float2 tex : TEXCOORD0;
	float3 viewPos : TEXCOORD1;
	float4 worldPos : TEXCOORD2;
};

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

PixelInputType Vshader(VertexInputType input)
{
    PixelInputType output;
    
    input.position.w = 1.0f;

	matrix FinalworldMatrix = mul(cbuff_OBJSpecificMatrix, cbuff_worldMatrix);
	
    output.position = mul(input.position, FinalworldMatrix);
	
	output.viewPos = cbuff_eyePos.xyz - output.position;
	output.worldPos = output.position;
	
    output.position = mul(output.position, cbuff_viewMatrix);
    output.position = mul(output.position, cbuff_projectionMatrix);
    
	output.tex = input.tex;
    
    output.normal = mul(input.normal, FinalworldMatrix);
	
    return output;
}

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float3 normals;
	float4 worldPos;
	
	float4 finalColor;
	
	normals = input.normal;
	worldPos = input.worldPos;
	
	float4 ambientLight = { 0.05f, 0.05f, 0.05f, 0.05f };
		
	float4 texColor = shaderTexture.Sample(SampleTypeWrap, input.tex);
	texColor = saturate(ambientLight * texColor);
	
	finalColor = texColor;
	
	MaterialData mat;
	
	mat.specularPower = cbuff_specularPower;
	mat.specularIntensity = cbuff_specularIntensity;
	
	CoreData core;
	
	core.viewPos = input.viewPos;
	core.worldPos = worldPos.xyz;
	core.normal = normals.xyz;
	
	for(int i = 0; i < MAX_LIGHTS; i++) {
		
		float3 LightDirection = worldPos.xyz - pointLights[i].lightPos;
		float distanceToPoint = length(LightDirection);
	
		//if(distanceToPoint > pointLights[i].range)
		//	return float4(0,0,0,0);
			
		LightDirection = normalize(LightDirection);		
	
		PointLightData pointLight;
	
		pointLight.distanceToPoint = distanceToPoint;
	
		pointLight.AttenConstant = pointLights[i].AttenConstant;
		pointLight.AttenLinear = pointLights[i].AttenLinear;
		pointLight.AttenExponent = pointLights[i].AttenExponent;
	
		pointLight.baseLight.intensity = pointLights[i].intensity;
		pointLight.baseLight.lightPos = pointLights[i].lightPos;
		pointLight.baseLight.lightDirection = LightDirection;
		pointLight.baseLight.lightColor = pointLights[i].lightColor;
	
		finalColor += calcPointLight(pointLight, mat, core);
	
	}
	
	return finalColor;
}