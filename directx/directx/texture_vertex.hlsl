cbuffer ConstantBuffer
{
	matrix transform;
};

struct VSOut
{
	float2 tex : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float2 tex : TexCoord)
{
	VSOut vsOut;
	vsOut.pos = mul(float4(pos, 1.0f), transform);
	vsOut.tex = tex;
	return vsOut;
}