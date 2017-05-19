#include "shaderUniforms.inc"

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float3 viewPos : VIEWPOS;
};

Texture2D colorTexture : !% PIXEL_SHADER gbuff_colors !%
Texture2D normalTexture : !% PIXEL_SHADER gbuff_normals !%
Texture2D positionTexture : !% PIXEL_SHADER gbuff_positions !%
Texture2D specularColorTexture : !% PIXEL_SHADER gbuff_specular !%
Texture2D shadowTexture : !% PIXEL_SHADER shadowmap !%

SamplerState ShadowMapSampler : !% PIXEL_SHADER SampleTypeWrap !%
SamplerState SampleTypePoint : !% PIXEL_SHADER SampleTypePoint !%

static const float EPSILON = 0.00001;

static const float bias = 0.001f;

float linstep(float min, float max, float v) 
{
	return clamp((v - min) / (max - min), 0, 1);
}

float ReduceLightBleeding(float p_max, float Amount) 
{
	return linstep(Amount, 1, p_max);
}

float3 Uncharted2Tonemap(float3 x) {

	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;

    return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

float chebyshevUpperBound(float2 moments, float ourdepth)
{
	if (moments.x < ourdepth)
		return 1.0;
	
	float variance = moments.y - (moments.x*moments.x);
	variance = max(variance,0.0000244);
	
	float d = ourdepth - moments.x;
	float p_max = variance / (variance + d*d);
	
	p_max = ReduceLightBleeding(p_max, 0.05f);
	
	return p_max;
}

float4 calcLight(BaseLightData light, MaterialData mat, CoreData coreData) 
{						
	float diffuseFactor = dot(coreData.normal.xyz, -light.lightDirection);
	
	float4 diffuseColor = float4(0,0,0,0);
	float4 specularColor = float4(0,0,0,0);
	
	if(diffuseFactor > 0) 
	{
		diffuseColor = float4(light.lightColor, 1.0) * light.intensity * diffuseFactor;
		
		float3 V = normalize(coreData.viewPos - coreData.worldPos.xyz);	
		float3 R = reflect(normalize(light.lightDirection), normalize(coreData.normal.xyz)); 
	
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
	
	float4 pos = float4(input.position, 1.0f);
	
	pos.w = 1.0f;
	
	output.position = mul(pos, cbuff_worldMatrix);
	output.position = mul(output.position, cbuff_camViewStart);
	output.position = mul(output.position, cbuff_orthoProjection);

	output.tex = input.tex;
	
	return output;
}
