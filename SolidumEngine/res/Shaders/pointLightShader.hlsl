#include "deferredLighting.hlsl"

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;
	float4 worldPos;
	float4 specuColor;
	
	colors = colorTexture.Sample(SampleTypePoint, input.tex);
	normals = normalTexture.Sample(SampleTypePoint, input.tex);
	worldPos = positionTexture.Sample(SampleTypePoint, input.tex);
	specuColor = specularColorTexture.Sample(SampleTypePoint, input.tex);
	
	float4 finalColor = colors;
	
	float3 LightDirection = worldPos.xyz - cbuff_lightPos;
	float distanceToPoint = length(LightDirection);
	
	if(distanceToPoint > cbuff_pointLightRange)
		return float4(0,0,0,0);
			
	LightDirection = normalize(LightDirection);		
	
	PointLightData pointLight;
	
	pointLight.distanceToPoint = distanceToPoint;
	
	pointLight.AttenConstant = cbuff_pointLightConstant;
	pointLight.AttenLinear = cbuff_pointLightLinear;
	pointLight.AttenExponent = cbuff_pointLightExponent;
	
	pointLight.baseLight.intensity = cbuff_lightIntensity;
	pointLight.baseLight.lightPos = cbuff_lightPos;
	pointLight.baseLight.lightDirection = LightDirection;
	pointLight.baseLight.lightColor = cbuff_lightColor;
	
	MaterialData mat;
	
	mat.specularPower = worldPos.w;
	mat.specularIntensity = normals.w;
	
	CoreData core;
	
	core.viewPos = input.viewPos;
	core.worldPos = worldPos.xyz;
	core.normal = normals.xyz;
	
	finalColor += calcPointLight(pointLight, mat, core);
	
	return finalColor;
}