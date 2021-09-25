cbuffer ConstantData
{
	float3 lightPos;
};

static const float3 materailColor = { 0.7f, 0.7f, 0.9f };
static const float3 ambientLight = { 0.05f, 0.05f, 0.05f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLinear = 0.045f;
static const float attQuadratic = 0.0075f;

float4 main(float3 pos: Position, float3 norm: Normal) : SV_Target
{
	const float3 lightDir = lightPos - pos;
	const float lightDist = length(lightDir);
	const float3 lightDirNorm = lightDir / lightDist;
	
	const float att = 1 / (attConst + attLinear * lightDist + attQuadratic * lightDist * lightDist);
	
	const float3 diffuseLight = diffuseColor * diffuseIntensity * att * max(0.0f, dot(lightDirNorm, norm));
	
	return float4(saturate(ambientLight + diffuseLight), 1.0f);
}