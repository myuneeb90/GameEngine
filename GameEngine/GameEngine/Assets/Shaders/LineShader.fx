cbuffer MatrixBuffer
{
	float4x4 WVP; 
	float4x4 World;
};

cbuffer MaterialSurface
{
	float4 LineColor;
};

struct VertexIn
{
	float3 position : POSITION;
};

struct VertexOut
{
	float4 position  : SV_POSITION;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.position = mul(float4(vin.position, 1.0f), WVP);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return LineColor;
}

technique11 DefaultTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
        SetPixelShader( CompileShader(ps_5_0, PS()));
    }
}
