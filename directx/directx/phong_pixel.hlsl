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

cbuffer ConstantData
{
    float3 materialColor;
};

float4 main(float3 pos: Position, float3 norm: Normal) : SV_Target
{
	const float3 lightDir = lightPos - pos;
	const float lightDist = length(lightDir);
	const float3 lightDirNorm = lightDir / lightDist;
	
	const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
	const float3 diffuseLight = diffuseColor * diffuseIntensity * att * max(0.0f, dot(lightDirNorm, norm));
	
    return float4(saturate((ambientLight + diffuseLight) * materialColor), 1.0f);
}