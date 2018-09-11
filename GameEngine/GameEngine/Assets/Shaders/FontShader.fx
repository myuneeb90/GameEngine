cbuffer MatrixBuffer
{
	float4x4 WVP; 
	float4x4 World;
};

cbuffer MaterialSurface
{
	float4 TextColor;
	float3 LightDirection;
	float Padding;
};

Texture2D MainTexture;
SamplerState MainTextureSampler
{
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
	vout.tex = vin.tex;
	vout.normal = mul(vin.normal, (float3x3)World);
	vout.normal = normalize(vout.normal);

    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
	float4 finalColor;

	finalColor = MainTexture.Sample(MainTextureSampler, pin.tex);

	float mask = finalColor.r;

	if(mask == 0.0f)
	{
		finalColor.a = 0.0f;
	}
	else
	{
		finalColor.a = 1.0f;
		finalColor = finalColor * TextColor;
	}

//	finalColor.a *= smoothstep(0.25f, 0.75f, mask);

//	if(finalColor.r == 0.0f)
//	{
//		finalColor.a = 0.0f;
//	}
//	else
//	{
//		finalColor.a = 1.0f;
//		finalColor = finalColor * TextColor;
//	}

    return finalColor;
}

technique11 FontBasicTech
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
        SetPixelShader( CompileShader(ps_5_0, PS()));
    }
}
