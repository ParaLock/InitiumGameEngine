cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix OBJSpecificMatrix;
	float3 eyeVec;
	float padding;
};

cbuffer LightBuffer
{
	float3 LightDirection;
	float padding1;
	float3 LightPos;
	float padding2;
	float4 AmbientColor;
	float4 LightColor;
	float3 eyeView;
	float padding5;
};

cbuffer Material
{
	//float Ns;
	//float Ni;
	//float d;
	//int illum;
	//float3 Ka;
	//float _padding1;
	//float3 Kd;
	//float _padding2;
	//float3 Ks;
	//float _padding3;
	//float3 Ke;
	//float _padding4;
	//float3 Ki;
	//float _padding5;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
};

PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	return output;
}

Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);

SamplerState SampleTypePoint : register(s0);

float4 Pshader(PixelInputType input) : SV_TARGET
{
	float specularPower = 100.0f;
	float spotPower = 10.0f;
	float3 emissive = 0.0f;
	float4 globalAmbient = { 1.2f, 1.2f, 1.2f, 1.2f };

	float3 Ke = 0.0f;
	float3 Ka = 0.2f;
	float3 Kd = 1.0f;
	float3 Ks = 0.3f;

	float3 ambient = Ka*globalAmbient;

	float4 normals;
	float4 color;


	normals = normalTexture.Sample(SampleTypePoint, input.tex);
	color = colorTexture.Sample(SampleTypePoint, input.tex);

	//Difuze
	float3 L = normalize(-LightPos - input.position);
	float diffuseLight = max(dot(normals,L), 0);
	float3 diffuse = Kd*LightColor*diffuseLight;

	//Specular
	float3 V = normalize(eyeVec - input.position);
	float3 H = normalize(L + V);
	float specularLight = pow(dot(normals,H),specularPower);
	if (diffuseLight <= 0) specularLight = 0;
	float3 specular = Ks * LightColor * specularLight;

	//spot scale
	float spotScale = pow(max(dot(L,-LightDirection),0),spotPower);

	//sum all light components
	float3 light = emissive + ambient + (diffuse + specular)*spotScale;

	//multiply by light
	color.rgb *= light;

	return color;
}
