cbuffer buff
{
	float4x4 mat;
};

struct VS_OUTPUT
{
float3 color : Color;
float4 position : SV_Position;
};

VS_OUTPUT main(float4 inPos : Position, float3 inColor : Color)
{
	VS_OUTPUT vso;
	
	vso.color = inColor;
	vso.position = mul(inPos, mat);
	
	return vso;
}