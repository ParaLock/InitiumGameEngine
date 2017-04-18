#include "deferredLighting.hlsl"

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float4 color;
	float4 normals;
	float4 worldPos;
	float4 specuColor;
	float4 lightVertPos;
	
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
	
	//const float bias = 0.001f;
	
	float bias = 0.005*tan(acos(0));
	bias = clamp(bias, 0,0.01);

	lightVertPos = mul(float4(worldPos.xyz, 1), cbuff_lightViewMatrix);
	lightVertPos = mul(lightVertPos, cbuff_lightProjectionMatrix);
	
	float2 ShadowTexC = 0.5f * lightVertPos.xy / lightVertPos.w + float2(0.5, 0.5);
	ShadowTexC.y = 1.0f - ShadowTexC.y;
	
	float2 shadowdepth = shadowTexture.Sample( ShadowMapSampler, ShadowTexC ).rg;
	float ourdepth = (1 - (lightVertPos.z / lightVertPos.w));

	float shadow = chebyshevUpperBound(shadowdepth, ourdepth);
	
	color = calcLight(light, mat, core) * shadow;
	
	return color;
}