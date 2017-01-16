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
	
	float diffuseFactor = dot(normals.xyz, -cbuff_lightDirection);
		
	if(diffuseFactor > 0) 
	{
		if(worldPos.w > 0) 
		{
			finalColor += calcSpecular(normals.xyz, specuColor, input.viewPosition, cbuff_lightDirection, 
				worldPos.xyz, worldPos.w, normals.w);
		}
		
		finalColor += calcDirectionalLight(normals.xyz, colors, cbuff_lightColor, cbuff_lightDirection);	
	
	}	
		
	return finalColor;
}