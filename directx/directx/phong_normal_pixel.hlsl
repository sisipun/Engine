cbuffer ConstantData : register(b0)
{
    float specularIntensity;
    float specularPower;
    bool normalMapEnabled;
};

cbuffer LightConstantData : register(b1)
{
    float3 lightPos;
    float3 ambientColor;
    float3 lightColor;
    float lightIntensity;
    float attConst;
    float attLinear;
    float attQuadratic;
};

cbuffer CameraConstantData : register(b2)
{
    float3 cameraPos;
};

Texture2D diffuseTex;
Texture2D normalTex;
SamplerState smplr;

float4 main(float3 worldPos : Position, float3 norm : Normal, float2 texCoord : Texcoord) : SV_Target
{
    if (normalMapEnabled)
    {
        const float3 normSample = normalTex.Sample(smplr, texCoord).xyz;
        norm.x = normSample.x * 2.0f - 1.0f;
        norm.y = -normSample.y * 2.0f + 1.0f;
        norm.z = -normSample.z;
    }
    
    const float3 lightToPos = lightPos - worldPos;
    const float lightDist = length(lightToPos);
    const float3 lightDir = lightToPos / lightDist;
    const float3 light = (lightColor * lightIntensity);
	
    const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
    const float3 ambientLight = ambientColor * light * att;
    
    const float3 diffuseColor = diffuseTex.Sample(smplr, texCoord).rgb;
    const float3 diffuseLight = diffuseColor * light * att * max(0.0f, dot(lightDir, normalize(norm)));
    
    const float3 viewDir = normalize(cameraPos - worldPos);
    const float3 reflectDir = normalize(reflect(-lightDir, norm));
    //const float3 halfway = normalize(viewDir + lightDir);
    //pow(max(0.0f, dot(halfway, normalize(norm))), specularPower)
    
    const float3 specularLight = specularIntensity * light * att * pow(max(0.0f, dot(viewDir, reflectDir)), specularPower);
    
    return float4(saturate(ambientLight + diffuseLight + specularLight), 1.0f);
}