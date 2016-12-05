cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
	matrix OBJSpecificMatrix;
};

struct VertexInputType
{
	float4 position : POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 tex : TEXCOORD;
};

struct PixelOutputType
{
	float4 color : SV_Target0;
	float4 normal : SV_Target1;
};


PixelInputType Vshader(VertexInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	matrix FinalworldMatrix = mul(OBJSpecificMatrix, worldMatrix);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, FinalworldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = normalize(mul(input.normal, (float3x3)FinalworldMatrix));

	return output;
}

Texture2D shaderTexture : register(t0);
SamplerState SampleTypeWrap : register(s0);

PixelOutputType Pshader(PixelInputType input) : SV_TARGET
{
	PixelOutputType output;

	float4 ambientLight = { 0.2f, 0.2f, 0.2f, 0.2f };

	// Sample the color from the texture and store it for output to the render target.
	output.color = shaderTexture.Sample(SampleTypeWrap, input.tex);
	output.color = saturate(ambientLight * output.color);

	// Store the normal for output to the render target.
	output.normal = float4(input.normal, 1.0f);

	return output;
}