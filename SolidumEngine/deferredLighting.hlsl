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
	float3 viewDirection : TEXCOORD1;
};

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D positionTexture : register(t2);
Texture2D specularColorTexture : register(t3);

SamplerState SampleTypePoint : register(s0);

float4 calcLight(float intensity, float3 lightDirection, float3 normal, 
		float3 lightColor) 
{						
	float diffuseFactor = dot(normal, -lightDirection);
	
	float4 diffuseColor = float4(0,0,0,0);
	
	if(diffuseFactor > 0) 
	{
		diffuseColor = float4(lightColor, 1.0) * intensity * diffuseFactor;
	}
	
	return diffuseColor;
}

float4 calcDirectionalLight(float3 normal, float4 color, float4 lightColor, float3 lightDirection) 
{
	float3 lightDir;
	float4 lightIntensity;
	float4 outputColor;

	lightDir = normalize(-lightDirection);

	lightIntensity = saturate(dot(normal, lightDir));

	lightIntensity *= lightColor;

	outputColor = color * lightIntensity;

	return outputColor;
}

float4 calcPointLight(float3 LightDirection, float3 normal, float intensity, float4 lightColor, float range, 
						float AttenConstant, float AttenLinear, float AttenExponent) 
{
	float distanceToPoint = length(LightDirection);
	
	if(distanceToPoint > range)
		return float4(0,0,0,0);
	
	float4 finalColor = calcLight(intensity, normalize(LightDirection), normal.xyz, lightColor);
	
	float attenuation = AttenConstant +
						AttenLinear * distanceToPoint +
						AttenExponent * distanceToPoint * distanceToPoint + 
						0.0001;
		
	
	return finalColor / attenuation; 					
}

float4 calcSpecular(float3 normal, float4 specColor, float3 viewDirection, float3 lightDirection,
	float3 worldPos, float specPower, float specIntensity) 
{
	float4 finalColor = float4(0,0,0,0);

	float3 Normal = normalize(normal);
	float3 ViewDirection = normalize(-viewDirection);
	float3 LightDirection = normalize(lightDirection - worldPos);
	
	float3 V = ViewDirection;
	
	float3 R = reflect(Normal, LightDirection); 
	
	finalColor = specIntensity * specColor * pow( saturate( dot( R, V ) ), specPower );
	
	return finalColor;
}

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 worldPos;
	
	worldPos = positionTexture[input.tex];
	
	output.viewDirection = cbuff_eyePos.xyz - worldPos.xyz;
	
	input.position.w = 1.0f;
	
	output.position = mul(input.position, cbuff_worldMatrix);
	output.position = mul(output.position, cbuff_camViewStart);
	output.position = mul(output.position, cbuff_orthoProjection);

	output.tex = input.tex;

	return output;
}