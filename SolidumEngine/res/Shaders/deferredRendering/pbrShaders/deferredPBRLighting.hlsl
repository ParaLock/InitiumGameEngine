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
Texture2D glowTexture : register(t2);

SamplerState SampleTypePoint : register(s0);

float3 ComputeLighting(GBUFFER_DATA gbufferData, float3 lightColor, 
                       float lightStrength, float3 lightDir, 
                       float3 viewDir, float attn)
{
    float3 H = normalize(viewDir + lightDir);
 
    float dotNL = saturate(dot(gbufferData.normal, lightDir));
    float dotNH = saturate(dot(gbufferData.normal, H));
    float dotNV = saturate(dot(gbufferData.normal, viewDir));
    float dotVH = saturate(dot(viewDir, H));
    float alpha = max(0.001f, gbufferData.roughness * gbufferData.roughness);

    float3 g_diffuse = pow(gbufferData.diffuseColor, 2.2);
    float3 g_lightColor = lightColor;

    float3 realAlbedo = g_diffuse - g_diffuse * gbufferData.metallic;

    float3 realSpecularColor = lerp(0.03f, g_diffuse, gbufferData.metallic);

    float3 albedoDiffuse = Albedo(realAlbedo);
    float3 specular = Specular(dotNL, dotNH, dotNV, 
                            dotVH, alpha, realSpecularColor);

    float3 finalColor = lightColor * dotNL 
                   * (albedoDiffuse * (1.0 - specular) + specular);
        
    return attn * (lightStrength * finalColor);
};


void unpackInput(float3 texCoord, inout GBUFFER_DATA output)
{
  //sample the base color
  float4 color = colorTexture.Sample(SampleTypePoint, texCoord);

  //set the base color
  output.diffuseColor.rgb = color.rgb;

  //sample the normal data (normal and depth)
  float4 NormalData = normalTexture.Sample(SampleTypePoint, texCoord);

  //convert to normal range then normalize
  output.normal = normalize(NormalData.xyz);

  //sample the spec power
  output.roughness = color.a;
  output.metallic = NormalData.w;

  //sample the depth in ndc space and leave to converting depth to different space by shaders
  output.ndcDepthZ = DepthTexture.Sample(SampleTypePoint, texCoord).r;
};

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