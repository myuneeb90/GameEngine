#include "CoreEngine/AppMain.h"

//===========================================
//---------------- Material -----------------
//===========================================
/*

Material::Material(ShaderFX *shader)
{
	Shader = shader;
	StartIndex = 0;
	IndexCount = 0;
}

Material::~Material()
{
	SAFE_DELETE(Shader);
}

ShaderFX* Material::GetShader()
{
	return Shader;
}

//===========================================
//------------ Standard Material ------------
//===========================================

StandardMaterial::StandardMaterial(ShaderFX *shader) : Material(shader)
{
	MainTexture = NULL;
	SamplerState = NULL;
}

StandardMaterial::~StandardMaterial()
{
	SAFE_DELETE(MainTexture);
	
	if(SamplerState != NULL)
	{
		SamplerState->Release();
		SamplerState = NULL;
	}
}

void StandardMaterial::LoadMainTexture(WCHAR *fileName)
{
	MainTexture = new Texture2D();
	MainTexture->Load(fileName);
	MainTexture->SourceID = 0;
	Shader->SetTexture("MainTexture", MainTexture->Source);
}

void StandardMaterial::CreateSamplerState()
{
	HRESULT result;
	D3D11_SAMPLER_DESC samplerDescription;

	samplerDescription.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDescription.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDescription.MipLODBias = 0.0f;
	samplerDescription.MaxAnisotropy = 1;
	samplerDescription.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDescription.BorderColor[0] = 0;
	samplerDescription.BorderColor[1] = 0;
	samplerDescription.BorderColor[2] = 0;
	samplerDescription.BorderColor[3] = 0;
	samplerDescription.MinLOD = 0;
	samplerDescription.MaxLOD = D3D11_FLOAT32_MAX;

	result = GlobalRefs::Graphics->Device->CreateSamplerState(&samplerDescription, &SamplerState);

	if(FAILED(result))
	{
		DISPLAY_MESSAGE(L"ERROR!!!", L"Failed to create sampler state");
		return;
	}

	return;
}

void StandardMaterial::BindMainTexture()
{
	if(MainTexture != NULL)
	{
		GlobalRefs::Graphics->DeviceContext->PSSetShaderResources(MainTexture->SourceID, 1, &MainTexture->Source);
	}
}

void StandardMaterial::BindSamplerState()
{
	if(SamplerState != NULL)
	{
		GlobalRefs::Graphics->DeviceContext->PSSetSamplers(0, 1, &SamplerState);
	}
}
*/