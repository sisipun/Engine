cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
}

struct VSInput
{
    float3 position : POSITION;
    float3 normal: NORMAL;
    float3 color : COLOR;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(mul(mul(float4(input.position, 1.0f), world), view), projection);
    output.color = input.color;

    return output;
}