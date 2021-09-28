cbuffer LightConstantData
{
    float3 lightPos;
    float3 ambientLight;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLinear;
    float attQuadratic;
};

cbuffer CameraConstantData
{
    float3 cameraPos;
};

cbuffer ConstantData
{
    float3 materialColors[6];
    float padding;
    float specularIntensity;
    float specularPower;
};

float4 main(float3 worldPos : Position, float3 norm : Normal, uint tid : SV_PrimitiveID) : SV_Target
{
    const float3 lightToPos = lightPos - worldPos;
    const float lightDist = length(lightToPos);
    const float3 lightDir = lightToPos / lightDist;
	
    const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
    const float3 diffuseLight = diffuseColor * diffuseIntensity * att * max(0.0f, dot(lightDir, normalize(norm)));
    
    const float3 viewDir = normalize(cameraPos - worldPos);
    const float3 halfway = normalize(viewDir + lightDir);
    const float3 reflection = 2.0f * norm * dot(lightDir, norm) - lightDir;
    const float3 specularLight = att * specularIntensity * pow(max(0.0f, dot(halfway, normalize(norm))), specularPower);
    
    return float4(saturate((ambientLight + diffuseLight + specularLight) * materialColors[(tid / 2) % 6]), 1.0f);
}