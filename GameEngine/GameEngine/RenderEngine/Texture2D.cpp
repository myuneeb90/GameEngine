#include "CoreEngine/AppMain.h"

Texture2D::Texture2D()
{
	Source = NULL;
	Pixels = NULL;
	Width = 0;
	Height = 0;
	SourceID = 0;
}

Texture2D::~Texture2D()
{
	this->Destroy();
}

void Texture2D::SetPixels(Color *pixels, int width, int height)
{
	Pixels = pixels;
	Width = width;
	Height = height;
}

Color* Texture2D::GetPixels()
{
	return Pixels;
}

void Texture2D::Apply()
{
	if(Pixels != NULL && Width != 0 && Height != 0)
	{
		ID3D11Texture2D *texture;
		D3D11_TEXTURE2D_DESC textureDesc;
		D3D11_SUBRESOURCE_DATA textureData;
		int bytesPerPixel = 16;

		textureData.pSysMem = Pixels;
		textureData.SysMemPitch = bytesPerPixel * Width;
		textureData.SysMemSlicePitch = 0;

		textureDesc.Width = Width;
		textureDesc.Height = Height;
		textureDesc.MipLevels          = 1;
		textureDesc.ArraySize          = 1;
		textureDesc.SampleDesc.Count   = 1;
		textureDesc.SampleDesc.Quality = 0;
		textureDesc.Usage              = D3D11_USAGE_DEFAULT;
		textureDesc.Format             = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags     = 0;
		textureDesc.MiscFlags          = 0;

		if(FAILED(GlobalRefs::Graphics->Device->CreateTexture2D(&textureDesc, &textureData, &texture)))
		{
			cout<<"Failed to create the texture 2d"<<endl;
		}

		GlobalRefs::Graphics->Device->CreateShaderResourceView(texture, NULL, &Source);
	}
}

void Texture2D::Load(WCHAR *fileName)
{
	HRESULT result;

	D3DX11_IMAGE_LOAD_INFO pLoadInfo;

	pLoadInfo.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	result = D3DX11CreateShaderResourceViewFromFile(GlobalRefs::Graphics->Device, fileName, &pLoadInfo, NULL, &Source, NULL);
	
	if(FAILED(result))
	{
		DISPLAY_MESSAGE(L"ERROR!!!", L"Failed to load texture");
		return;
	}
}

void Texture2D::Destroy()
{
	if(Source)
	{
		Source->Release();
		Source = NULL;
	}
}