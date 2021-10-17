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

Texture2D diffuseTex;
Texture2D specularTex;
SamplerState smplr;

float4 main(float3 worldPos : Position, float3 norm : Normal, float2 texCoord : Texcoord) : SV_Target
{
    const float3 lightToPos = lightPos - worldPos;
    const float lightDist = length(lightToPos);
    const float3 lightDir = lightToPos / lightDist;
	
    const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
    const float3 diffuseLight = diffuseColor * diffuseIntensity * att * max(0.0f, dot(lightDir, normalize(norm)));
    
    const float3 viewDir = normalize(cameraPos - worldPos);
    const float3 halfway = normalize(viewDir + lightDir);
    
    const float4 specularSample = specularTex.Sample(smplr, texCoord);
    const float3 specularColor = specularSample.rgb;
    const float specularPower = pow(2.0f, specularSample.a * 13.0f);
    const float3 specularLight = att * (diffuseColor * diffuseIntensity) * pow(max(0.0f, dot(halfway, normalize(norm))), specularPower);
    
    return float4(saturate((ambientLight + diffuseLight) * diffuseTex.Sample(smplr, texCoord).rgb + specularLight * specularColor), 1.0f);
}