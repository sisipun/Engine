float3 mapNormal(const float3 tan, const float3 bitan, const float3 norm, const float2 texCoord, Texture2D normalTex, SamplerState smplr)
{
    const float3x3 tanToModel = float3x3(tan, bitan, norm);
    const float3 normSample = normalTex.Sample(smplr, texCoord).xyz;
    const float3 tanNormal = normSample * 2.0f - 1.0f;
    
    return normalize(mul(tanNormal, tanToModel));
}

float attenuate(uniform float attConst, uniform float attLinear, uniform float attQuadratic, const in float lightDist)
{
    return 1.0f / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
}

float3 ambient(const in float3 ambientColor, const in float3 diffuseColor, const in float att, const in float3 light)
{
    return ambientColor * diffuseColor * light * att;
}

float3 diffuse(const in float3 diffuseColor, const in float att, const in float3 light, const in float3 lightDir, const in float3 norm)
{
    return diffuseColor * light * att * max(0.0f, dot(lightDir, normalize(norm)));
}

float3 speculate(
    const in float3 specularColor,
    const float specularPower,
    const in float att,
    const in float3 light,
    const in float3 lightDir,
    const in float3 worldPos,
    const in float3 norm,
    const in float3 cameraPos
)
{
    const float3 viewDir = normalize(cameraPos - worldPos);
    const float3 reflectDir = normalize(reflect(-lightDir, norm));
    return specularColor * light * att * pow(max(0.0f, dot(viewDir, reflectDir)), specularPower);
}