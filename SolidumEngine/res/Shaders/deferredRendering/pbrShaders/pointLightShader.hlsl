#include "deferredPBRLighting.hlsl"

float3 Pshader(PixelInputType input) : SV_TARGET
{
	float4 colors;
	float4 normals;
	
	GBUFFER_DATA inputData;
	
	unpackInput(input.tex, inputData);
	
	float3 LightDirection = "reconstructed worldPos" - cbuff_lightPos;
	float distanceToPoint = length(LightDirection);
	
	if(distanceToPoint > cbuff_pointLightRange)
		return float4(0,0,0,0);
	
	float attenuation = cbuff_pointLightConstant +
					cbuff_pointLightLinear * light.distanceToPoint +
					cbuff_pointLightExponent * light.distanceToPoint * light.distanceToPoint + 
					0.0001;
	
	return ComputeLighting(inputData, cbuff_lightColor, 
		cbuff_lightIntensity, LightDirection, input.viewPos, attenuation);
}