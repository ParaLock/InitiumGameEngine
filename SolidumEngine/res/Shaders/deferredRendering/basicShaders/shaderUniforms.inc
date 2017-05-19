cbuffer MatrixBuffer
{
	matrix cbuff_OBJSpecificMatrix;
	float3 cbuff_eyePos;
	float padding;
	matrix cbuff_worldMatrix;
	matrix cbuff_viewMatrix;
	matrix cbuff_camViewStart;
	matrix cbuff_projectionMatrix;
	matrix cbuff_orthoProjection;
	
	float4x4 cbuff_skydomeWorldViewProj;
	
	float4 cbuff_skydomeApexColor;
	float4 cbuff_skydomeCenterColor;
	
	matrix cbuff_lightDepthProjection;
	matrix cbuff_lightDepthView;
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
	
	matrix cbuff_lightProjectionMatrix;
	matrix cbuff_lightViewMatrix;
};

struct CoreData 
{
	float3 viewPos;
	float3 worldPos;
	float3 normal;
};

struct MaterialData 
{
	float specularPower;
	float specularIntensity;
};

struct BaseLightData 
{
	float intensity;
	float3 lightPos;
	float3 lightDirection;
	float3 lightColor;
};

struct PointLightData 
{
	BaseLightData baseLight;

	float distanceToPoint;
	
	float AttenConstant;
	float AttenLinear;
	float AttenExponent;
};

