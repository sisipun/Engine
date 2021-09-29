cbuffer ConstantData
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VSOut
{
    float3 worldPos : Position;
    float3 norm : Normal;
    float3 color : Color;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float3 norm : Normal, float3 color : Color)
{
    VSOut vsOut;
    vsOut.worldPos = (float3) mul(float4(pos, 1.0f), model);
    vsOut.norm = mul(norm, (float3x3) model);
    vsOut.pos = mul(mul(mul(float4(pos, 1.0f), model), view), projection);
    vsOut.color = color;
    return vsOut;
}