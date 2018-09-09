#ifndef SHADER_H
#define SHADER_H

enum ShaderType
{
	ST_MESH = 0,
	ST_LINE = 1
};

class Shader
{
	private:
			ID3DX11Effect *EffectPtr;
			ID3DX11EffectTechnique *EffectTechnique;
			string TechniqueName;
			ID3D11InputLayout *InputLayout;
			D3D11_INPUT_ELEMENT_DESC *InputLayoutDesc;
			int InputLayoutElementCount;	
			ShaderType Type;
	private:
			void OutputShaderErrorMessage(ID3D10Blob *errorMessage);
	public:
			Shader(string techniqueName, ShaderType type = ST_MESH);
			virtual ~Shader();

			void BuildShader(WCHAR *fileName);

			void BuildInputLayout();			
			void RenderInputLayout();
			void RenderShader(int indexCount);

			ShaderType GetShaderType();
			ID3D11InputLayout* GetInputLayout();
			ID3DX11EffectTechnique* GetEffectTechnique();
			void Destroy();

			void SetScalar(string name, float value);
			void SetScalar(string name, int value);
			void SetScalar(string name, bool value);
			void SetVector(string name, Vector4f value);
			void SetMatrix(string name, Matrix4x4f value);
			void SetMatrix(string name, Matrix4x4d value);
			void SetTexture(string name, ID3D11ShaderResourceView *texture);
};

#endif 