#include "base_shader.hlsl"

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
    norm = hasNormal ? mapNormal(normalize(tan), normalize(bitan), normalize(norm), texCoord, normalTex, smplr) : normalize(norm);
    
    const float3 lightToPos = lightPos - worldPos;
    const float lightDist = length(lightToPos);
    const float3 lightDir = lightToPos / lightDist;
    const float3 light = (lightColor * lightIntensity);
	
    const float att = attenuate(attConst, attLinear, attQuadratic, lightDist);
    
    const float3 diffuseColor = hasDiffuse ? diffuseTex.Sample(smplr, texCoord).rgb : materialColor;
    
    const float3 ambientLight = ambient(ambientColor, diffuseColor, att, light);
    const float3 diffuseLight = diffuse(diffuseColor, att, light, lightDir, norm);
    
    const float4 specularSample = specularTex.Sample(smplr, texCoord);
    const float specularPower = hasSpecularAlpha ? pow(2.0f, specularSample.a * 13.0f) : specularShininess;
    const float3 specularColor = hasSpecular ? specularSample.rgb : specularIntensity;
    const float3 specularLight = speculate(specularColor, specularPower, att, light, lightDir, worldPos, norm, cameraPos);
    
    return float4(saturate(ambientLight + diffuseLight + specularLight), 1.0f);
}