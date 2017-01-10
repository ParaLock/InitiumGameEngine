cbuffer MatrixBuffer
{
	float3 eyePos;
	int lightType;
	matrix worldMatrix;
	matrix viewMatrix;
	matrix camViewStart;
	matrix projectionMatrix;
	matrix orthoProjection;
	matrix OBJSpecificMatrix;
};

cbuffer LightBuffer
{
	float3 padding1;
	int materialID;
	float3 lightDirection;
	float specularIntensity;
	float3 lightPos;
	float specularPower;
	float4 ambientColor;
	float4 lightColor;
    float4 specularColor;
};