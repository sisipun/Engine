cbuffer ConstantData
{
	matrix model;
	matrix view;
	matrix projection;
};

float4 main(float3 pos : Position) : SV_Position
{
	return mul(mul(mul(float4(pos, 1.0f), model), view), projection);
}