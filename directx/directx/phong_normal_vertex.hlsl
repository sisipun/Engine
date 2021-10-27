cbuffer ConstantData : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

struct VSOut
{
    float3 worldPos : Position;
    float3 norm : Normal;
    float3 tan : Tangent;
    float3 bitan : Bitangent;
    float2 texCoord : Texcoord;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float3 norm : Normal, float3 tan : Tangent, float3 bitan : Bitangent, float2 texCoord : Texcoord)
{
    VSOut vsOut;
    vsOut.worldPos = (float3) mul(float4(pos, 1.0f), model);
    vsOut.norm = mul(norm, (float3x3) model);
    vsOut.tan = mul(tan, (float3x3) model);
    vsOut.bitan = mul(bitan, (float3x3) model);
    vsOut.texCoord = texCoord;
    vsOut.pos = mul(mul(mul(float4(pos, 1.0f), model), view), projection);
    return vsOut;
}