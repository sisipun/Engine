struct VSOut 
{
    float4 position : SV_POSITION;
    float3 color : COLOR;
};

VSOut main(float4 position : POSITION, float3 normal: NORMAL, float3 color : COLOR)
{
    VSOut output;

    output.position = position;
    output.color = color;

    return output;
}