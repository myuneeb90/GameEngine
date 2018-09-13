cbuffer MatrixBuffer
{
	float4x4 WVP; 
	float4x4 World;
};

cbuffer MaterialSurface
{
	float4 DiffuseColor;
//	float2 TextureTile;
//	float3 LightDirection;
//	float Padding;
};

Texture2D MainTexture;
SamplerState MainTextureSampler
{
//	Filter = MIN_LINEAR_MAG_MIP_POINT;
	Filter = ANISOTROPIC;
	MaxAnisotropy = 1;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VertexOut
{
	float4 position  : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;	
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.position = mul(float4(vin.position, 1.0f), WVP);
//	vout.tex = vin.tex;
//	vout.normal = mul(vin.normal, (float3x3)World);
//	vout.normal = normalize(vout.normal);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
//	float4 finalColor = float4(0, 0, 0, 0);
//	float lightIntensity;

//	finalColor.xyz = float3(0.1f, 0.1f, 0.1f) * DiffuseColor.xyz;
//	lightIntensity = saturate(dot(pin.normal, -LightDirection));
	
//	if(lightIntensity > 0.0f)
//	{
//		finalColor += (DiffuseColor * lightIntensity);
//	}

//	finalColor = saturate(finalColor);

    return float4(1, 0, 0, 1);//* MainTexture.Sample(MainTextureSampler, pin.tex * TextureTile);
}

technique11 DefaultTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}
