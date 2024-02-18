cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float3 lightDirection;
    float3 cameraPosition;
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
    float3 worldPosition : POSITION;
    float3 normal: NORMAL;
    float3 color : COLOR;
};

VSOutput main(VSInput input)
{
    VSOutput output;

    output.position = mul(mul(mul(float4(input.position, 1.0f), world), view), projection);
    output.worldPosition = mul(input.position, world);
    output.normal = mul(input.normal, world);
    output.color = input.color;

    output.position.x = -output.position.x; // Temp solution to flip x axis
    return output;
}