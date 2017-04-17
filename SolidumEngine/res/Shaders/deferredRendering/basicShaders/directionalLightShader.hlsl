#include "deferredLighting.hlsl"

static const float SMAP_SIZE = 2048.0f;
static const float SMAP_DX = 1.0f / SMAP_SIZE;

SamplerComparisonState samShadow
{
    Filter   = COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
    AddressU = BORDER;
    AddressV = BORDER;
    AddressW = BORDER;
    BorderColor = float4(0.0f, 0.0f, 0.0f, 0.0f);

    ComparisonFunc = LESS;
};

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
	
	float3 shadowPosH = lightVertPos.xyz / lightVertPos.w;
	
	shadowPosH = shadowPosH * 0.5 + 0.5;
	
	float depth = shadowPosH.z;
	
	const float dx = SMAP_DX;
	
	float percentLit = 0.0f;
    const float2 offsets[9] = 
    {
        float2(-dx,  -dx), float2(0.0f,  -dx), float2(dx,  -dx),
        float2(-dx, 0.0f), float2(0.0f, 0.0f), float2(dx, 0.0f),
        float2(-dx,  +dx), float2(0.0f,  +dx), float2(dx,  +dx)
    };
	
	[unroll]
    for(int i = 0; i < 9; ++i)
    {
        percentLit += shadowTexture.SampleCmpLevelZero(samShadow, 
            shadowPosH.xy + offsets[i], depth).r;
    }
	
	float final = percentLit /= 9.0f;
	
	color = calcLight(light, mat, core) * final;
	
	return color;
}