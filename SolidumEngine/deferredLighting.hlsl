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

float4 calcDirectionalLight(float4 normal, float4 color) 
{
	float3 lightDir;
	float4 lightIntensity;
	float4 outputColor;

	lightDir = normalize(-lightDirection);

	lightIntensity = saturate(dot(normal.xyz, lightDir));

	lightIntensity *= lightColor;

	outputColor = color * lightIntensity;

	return outputColor;
}

float4 calcSpecular(float4 normal, float4 specColor, float3 viewDirection, 
	float3 worldPos, float specPower, float specIntensity) 
{

	float4 finalColor;

	float3 Normal = normalize(normal.xyz);
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
	
	output.viewDirection = eyePos.xyz - worldPos.xyz;
	
	input.position.w = 1.0f;
	
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, camViewStart);
	output.position = mul(output.position, orthoProjection);

	output.tex = input.tex;

	return output;
}

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
	
	float diffuseFactor = dot(normals, -lightDirection);
	
	if(diffuseFactor > 0) {
		
		if(worldPos.w > 0) 
		{
			finalColor += calcSpecular(normals, specuColor, input.viewDirection, worldPos.xyz, worldPos.w, normals.w);
		}
		
		finalColor += calcDirectionalLight(normals, colors);	
	}
	
	return finalColor;
}
