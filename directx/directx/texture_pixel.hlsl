Texture2D tex;
SamplerState smplr;

float4 main(float coords : TexCoord) : SV_Target
{
	return tex.Sample(smplr, coords);
}