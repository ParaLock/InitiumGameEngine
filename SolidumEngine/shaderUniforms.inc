cbuffer MatrixBuffer
{
	float3 viewVector;
	float padding;
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix OBJSpecificMatrix;
};

cbuffer LightBuffer
{
	float3 lightDirection;
	float padding1;
	float3 lightPos;
	float specularPower;
	float4 ambientColor;
	float4 lightColor;
    float4 specularColor;
};