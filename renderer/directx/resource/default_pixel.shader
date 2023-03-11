cbuffer ConstantBuffer : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
    float4 lightDirection;
    float4 cameraPosition;
}

struct PSInput
{
    float4 position : SV_POSITION;
    float4 worldPosition : POSITION;
    float3 normal : NORMAL;
    float3 color : COLOR;
};


float4 main(PSInput input) : SV_TARGET
{
    float3 ambient = float3(0.1f, 0.1f, 0.1f);

    float3 normal = normalize(input.normal);
    float3 normalLigthDirection = normalize(lightDirection.xyz);

    float diffuseValue = max(dot(normal, -normalLigthDirection), 0.0f);
    float3 diffuse = float3(diffuseValue, diffuseValue, diffuseValue);

    float3 normalViewDirection = normalize(input.worldPosition.xyz - cameraPosition.xyz);
    float3 halfway = -normalize(normalViewDirection + normalLigthDirection);

    float specularValue = pow(max(dot(normal, halfway), 0.0f), 16.0f);
    float3 specular = float3(specularValue, specularValue, specularValue);

    float3 light = ambient + diffuse + specular;
    return float4(light * input.color, 1.0f);
}