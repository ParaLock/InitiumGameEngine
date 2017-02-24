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
	matrix cbuff_lightViewMatrix;
	matrix cbuff_lightProjectionMatrix;
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

