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
	float3 viewPos : TEXCOORD1;
};

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D positionTexture : register(t2);
Texture2D specularColorTexture : register(t3);
Texture2D shadowTexture : register(t4);

SamplerState SampleTypePoint : register(s0);

float4 calcLight(BaseLightData light, MaterialData mat, CoreData coreData) 
{						
	float diffuseFactor = dot(coreData.normal.xyz, -light.lightDirection);
	
	float4 diffuseColor = float4(0,0,0,0);
	float4 specularColor = float4(0,0,0,0);
	
	if(diffuseFactor > 0) 
	{
		diffuseColor = float4(light.lightColor, 1.0) * light.intensity * diffuseFactor;
		
		float3 V = normalize(coreData.viewPos - coreData.worldPos);	
		float3 R = reflect(normalize(normalize(light.lightDirection)), normalize(coreData.normal.xyz)); 
	
		specularColor = mat.specularIntensity * float4(light.lightColor, 1) 
			* pow( saturate( dot( R, V ) ), mat.specularPower );
	}
	
	return diffuseColor + specularColor;
}

float4 calcPointLight(PointLightData light, MaterialData mat, CoreData core) 
{
	light.baseLight.lightDirection = normalize(light.baseLight.lightDirection);

	float4 finalColor = calcLight(light.baseLight, mat, core);
	
	float attenuation = light.AttenConstant +
						light.AttenLinear * light.distanceToPoint +
						light.AttenExponent * light.distanceToPoint * light.distanceToPoint + 
						0.0001;
	
	return finalColor / attenuation; 					
}


PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	float4 worldPos = positionTexture[input.tex];
	
	output.viewPos = cbuff_eyePos.xyz - worldPos.xyz;
	
	input.position.w = 1.0f;
	
	output.position = mul(output.position, cbuff_worldMatrix);
	output.position = mul(input.position, cbuff_camViewStart);
	output.position = mul(output.position, cbuff_orthoProjection);

	output.tex = input.tex;

	return output;
}