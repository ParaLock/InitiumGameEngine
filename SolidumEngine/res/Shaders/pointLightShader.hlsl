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
	
	float diffuseFactor = dot(normals.xyz, -LightDirection);
	
	if(diffuseFactor > 0) 
	{
		if(worldPos.w > 0) 
		{
		
			finalColor += calcSpecular(normals.xyz, specuColor, input.viewPosition, LightDirection, 
					worldPos.xyz, worldPos.w, normals.w);
		}
			
		finalColor += calcPointLight(LightDirection, normals.xyz, cbuff_lightIntensity, cbuff_lightColor, cbuff_pointLightRange, 
							cbuff_pointLightConstant, 
							cbuff_pointLightLinear, 
							cbuff_pointLightExponent);
	}
	

	return finalColor;
}