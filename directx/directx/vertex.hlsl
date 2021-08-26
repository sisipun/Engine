cbuffer ConstantData
{
	matrix transform;
	float4 face_colors[6];
};

float4 main(float3 position : Position) : SV_Position
{
	return mul(float4(position, 1.0f), transform);
}