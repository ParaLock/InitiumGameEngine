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

	return output;
}