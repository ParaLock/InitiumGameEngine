cbuffer MatrixBuffer
{
	float3 eyePos;
	float padding;
	matrix worldMatrix;
	matrix viewMatrix;
	matrix camViewStart;
	matrix projectionMatrix;
	matrix orthoProjection;
	matrix OBJSpecificMatrix;
};

cbuffer LightBuffer
{
	float3 lightDirection;
	float specularShininess;
	float3 lightPos;
	float specularPower;
	float4 ambientColor;
	float4 lightColor;
    float4 specularColor;
};