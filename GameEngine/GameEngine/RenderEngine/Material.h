#ifndef MATERIAL_H
#define MATERIAL_H

struct Material
{
	Color DiffuseColor;
};

/*
class Material
{
	protected:
			  ShaderFX *Shader;
	public:
		   int StartIndex;
		   int IndexCount;
		   Color DiffuseColor;
	public:
			Material(ShaderFX *shader);
			virtual ~Material();

			ShaderFX* GetShader();
};

class StandardMaterial : public Material
{
	public:
		   Texture2D *MainTexture;
		   ID3D11SamplerState *SamplerState;
	public:
			StandardMaterial(ShaderFX *shader);
			virtual ~StandardMaterial();

			void LoadMainTexture(WCHAR *fileName);
			void CreateSamplerState();

			void BindMainTexture();
			void BindSamplerState();
};
*/

#endif