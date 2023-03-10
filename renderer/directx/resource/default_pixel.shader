cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float3 lightDirection;
    float3 cameraPosition;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float3 color : COLOR;
};


float4 main(PSInput input) : SV_TARGET
{
    return float4(input.color, 1.0f);
}