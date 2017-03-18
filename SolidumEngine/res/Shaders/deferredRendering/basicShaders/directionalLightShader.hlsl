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
	
	BaseLightData light;
	
	light.intensity = cbuff_lightIntensity;
	light.lightPos = cbuff_lightPos;
	light.lightDirection = cbuff_lightDirection;
	light.lightColor = cbuff_lightColor;
	
	MaterialData mat;
	
	mat.specularPower = worldPos.w;
	mat.specularIntensity = normals.w;
	
	CoreData core;
	
	core.viewPos = input.viewPos;
	core.worldPos = worldPos.xyz;
	core.normal = normals.xyz;

	finalColor += calcLight(light, mat, core);
	
	return finalColor;
}