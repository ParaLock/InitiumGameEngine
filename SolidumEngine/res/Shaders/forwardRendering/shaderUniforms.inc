#define MAX_LIGHTS 9

struct PointLight 
{
	float3 lightPos;
	float range;
	float3 lightDirection;
	float intensity;
	float4 lightColor;
	
	float AttenConstant;
	float AttenLinear;
	float AttenExponent;
	float padding3;
};

struct DirectionalLight 
{
	float3 lightPos;
	float intensity;
	float3 lightDirection;
	float padding4;
	float4 lightColor;
};

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
	

	float4 cbuff_ambientColor;
};

cbuffer LightBuffer
{		
	float cbuff_specularIntensity;
	float cbuff_specularPower;
	float2 padding1;
	PointLight pointLights[MAX_LIGHTS];
	//DirectionalLight directionalLights[MAX_LIGHTS];
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

