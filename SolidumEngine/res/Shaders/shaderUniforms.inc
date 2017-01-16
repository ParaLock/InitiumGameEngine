cbuffer MatrixBuffer
{
	float3 cbuff_eyePos;
	float padding;
	matrix cbuff_worldMatrix;
	matrix cbuff_viewMatrix;
	matrix cbuff_camViewStart;
	matrix cbuff_projectionMatrix;
	matrix cbuff_orthoProjection;
	matrix cbuff_OBJSpecificMatrix;
};

cbuffer LightBuffer
{
	float3 cbuff_lightDirection;
	float cbuff_specularIntensity;
	float3 cbuff_lightPos;
	float cbuff_specularPower;
	float4 cbuff_ambientColor;
	float4 cbuff_lightColor;
    float4 cbuff_specularColor;
	float cbuff_lightIntensity;
	float cbuff_pointLightConstant;
	float cbuff_pointLightLinear;
	float cbuff_pointLightExponent;
	
	float cbuff_pointLightRange;
	float3 padding2;
};