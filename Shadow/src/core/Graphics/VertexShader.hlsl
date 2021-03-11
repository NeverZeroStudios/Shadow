struct VS_OUTPUT {
	float3 color : Color;
	float4 position : SV_Position;
};

VS_OUTPUT main(float3 inPos : Position, float3 inColor : Color)
{
	VS_OUTPUT vso;
	
	vso.color = inColor;
	vso.position = float4(inPos, 1.0f);
	
	return vso;
}