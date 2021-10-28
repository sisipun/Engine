cbuffer ConstantData : register(b0)
{
    float3 materialColor;
    bool hasDiffuse;
    bool hasNormal;
    float3 specularIntensity;
    bool hasSpecular;
    bool hasSpecularAlpha;
    float specularShininess;
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

Texture2D diffuseTex : register(t0);
Texture2D normalTex : register(t1);
Texture2D specularTex : register(t2);

SamplerState smplr;

float4 main(float3 worldPos : Position, float3 norm : Normal, float3 tan : Tangent, float3 bitan : Bitangent, float2 texCoord : Texcoord) : SV_Target
{
    if (hasNormal)
    {
        const float3x3 tanToModel = float3x3(
            normalize(tan),
            normalize(bitan),
            normalize(norm)
        );
        
        const float3 normSample = normalTex.Sample(smplr, texCoord).xyz;
        norm.x = normSample.x * 2.0f - 1.0f;
        norm.y = -normSample.y * 2.0f + 1.0f;
        norm.z = normSample.z;
        
        norm = mul(norm, tanToModel);
    }
    
    const float3 lightToPos = lightPos - worldPos;
    const float lightDist = length(lightToPos);
    const float3 lightDir = lightToPos / lightDist;
    const float3 light = (lightColor * lightIntensity);
	
    const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
    const float3 ambientLight = ambientColor * light * att;
    
    const float3 diffuseColor = hasDiffuse ? diffuseTex.Sample(smplr, texCoord).rgb : materialColor;
    const float3 diffuseLight = diffuseColor * light * att * max(0.0f, dot(lightDir, normalize(norm)));
    
    const float3 viewDir = normalize(cameraPos - worldPos);
    const float3 reflectDir = normalize(reflect(-lightDir, norm));

    const float4 specularSample = specularTex.Sample(smplr, texCoord);
    const float specularPower = hasSpecularAlpha ? pow(2.0f, specularSample.a * 13.0f) : specularShininess;
    const float3 specularColor = hasSpecular ? specularSample.rgb : specularIntensity;
    const float3 specularLight = specularColor * light * att * pow(max(0.0f, dot(viewDir, reflectDir)), specularPower);
    
    return float4(saturate(diffuseLight), 1.0f);
}