#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class Texture2D
{			
	public:
			ID3D11ShaderResourceView *Source;
			Color *Pixels;
			int Width;
			int Height;
			int SourceID;
	public:
			Texture2D();
			~Texture2D();

		//	void MakeCheckerBoardTexture();
			void SetPixels(Color *pixels, int width, int height);
			Color* GetPixels();
			void Apply();
			void Load(WCHAR *fileName);
			void Destroy();
};

#endif