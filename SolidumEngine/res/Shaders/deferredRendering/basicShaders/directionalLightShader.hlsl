#include "deferredLighting.hlsl"

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float4 color;
	float4 normals;
	float4 worldPos;
	float4 specuColor;
	
	color = colorTexture.Sample(SampleTypePoint, input.tex);
	normals = normalTexture.Sample(SampleTypePoint, input.tex);
	worldPos = positionTexture.Sample(SampleTypePoint, input.tex);
	specuColor = specularColorTexture.Sample(SampleTypePoint, input.tex);
	
	BaseLightData light;
	
	light.intensity = cbuff_lightIntensity;
	light.lightPos = cbuff_lightPos;
	light.lightDirection = cbuff_lightDirection;
	light.lightColor = cbuff_lightColor;
	
	MaterialData mat;
	
	mat.specularPower = specuColor.w;
	mat.specularIntensity = normals.w;
	
	CoreData core;
	
	core.viewPos = input.viewPos;
	core.worldPos = worldPos.xyz;
	core.normal = normals.xyz;
	
	float4 lightVertPos = mul(float4(worldPos.xyz, 1), cbuff_lightSpaceMatrix);
	
	float3 projCoords = lightVertPos.xyz / lightVertPos.w;
	
	projCoords = projCoords * 0.5 + 0.5;
	
	float closestDepth = shadowTexture.Sample(ShadowMapSampler, projCoords.xy).r;

    float currentDepth = projCoords.z;

    float bias = 0.005;
    float shadow = (currentDepth - bias) > closestDepth ? 1.0 : 0.0;

    if(projCoords.z > 1.0) {
        shadow = 0.0;
    }
	
	color = calcLight(light, mat, core) * shadow;
	
	return color;
}