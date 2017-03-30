#include "deferredLighting.hlsl"

float readShadowMap(float3 worldPos)
{
	float4 lightViewSpace = mul(float4(worldPos, 1), cbuff_lightViewProj);
	
	lightViewSpace = lightViewSpace / lightViewSpace.w;
	
	float2 textureCoordinates = lightViewSpace.xy * float2(0.5,0.5) + float2(0.5,0.5);
	
	const float bias = 0.0001;
	
	float depthValue = shadowTexture.Sample(SampleTypePoint, textureCoordinates) - bias;
	
	return lightViewSpace.z * 0.5 + 0.5 < depthValue;
	
}

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float4 color;
	float4 normals;
	float4 worldPos;
	float4 specuColor;
	float4 lightSpace;
	
	color = colorTexture.Sample(SampleTypePoint, input.tex);
	normals = normalTexture.Sample(SampleTypePoint, input.tex);
	worldPos = positionTexture.Sample(SampleTypePoint, input.tex);
	specuColor = specularColorTexture.Sample(SampleTypePoint, input.tex);
	lightSpace = lightSpaceMap.Sample(SampleTypePoint, input.tex);
	
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

	float4 lightViewPosition = lightSpace;//mul(float4(worldPos.xyz, 1), cbuff_lightViewProj);
	
	float2 projectTexCoord;
	
	projectTexCoord.x =  lightViewPosition.x / lightViewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -lightViewPosition.y / lightViewPosition.w / 2.0f + 0.5f;

	float depthValue;
	float lightDepthValue;
	
	const float bias = 0.0001;
	
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		depthValue = shadowTexture.Sample(SampleTypePoint, projectTexCoord).r;

		lightDepthValue = lightViewPosition.z / lightViewPosition.w;

		lightDepthValue = lightDepthValue - bias;
		
		if(lightDepthValue < depthValue)
		{
			color = calcLight(light, mat, core);
		}
	}
	
	return color;
}