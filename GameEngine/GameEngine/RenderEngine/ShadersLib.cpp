#include "CoreEngine/AppMain.h"

Shader* ShadersLib::CreateDefaultShader(Color diffuseColor)
{
	wstring path = SHADERPATH;
	path.append(L"Default.fx");

	Shader *shader = NULL;

	shader = new Shader("DefaultTech");
	shader->BuildShader(L"../GameEngine/Assets/Shaders/Default.fx");
	shader->BuildInputLayout();

	shader->SetVector("DiffuseColor", Vector4f(diffuseColor.Red, diffuseColor.Green, diffuseColor.Blue, diffuseColor.Alpha));
	shader->SetVector("TextureTile", Vector4f(1, 1, 1, 1));

	return shader;
}

Shader* ShadersLib::CreateLineShader(Color lineColor)
{
	wstring path = SHADERPATH;
	path.append(L"LineShader.fx");

	Shader *shader = NULL;

	shader = new Shader("DefaultTech", ST_LINE);
	shader->BuildShader((WCHAR*)path.c_str());
	shader->BuildInputLayout();

	shader->SetVector("LineColor", Vector4f(lineColor.Red, lineColor.Green, lineColor.Blue, lineColor.Alpha));

	return shader;
}

Shader* ShadersLib::CreateSpriteShader(Color diffuseColor)
{
	wstring path = SHADERPATH;
	path.append(L"SpriteShader.fx");

	Shader *shader = NULL;

	shader = new Shader("SpriteBasicTech");
	shader->BuildShader((WCHAR*)path.c_str());
	shader->BuildInputLayout();

	shader->SetVector("DiffuseColor", Vector4f(diffuseColor.Red, diffuseColor.Green, diffuseColor.Blue, diffuseColor.Alpha));

	return shader;
}

Shader* ShadersLib::CreateFontShader(Color textColor)
{
	wstring path = SHADERPATH;
	path.append(L"FontShader.fx");

	Shader *shader = NULL;

	shader = new Shader("FontBasicTech");
	shader->BuildShader((WCHAR*)path.c_str());
	shader->BuildInputLayout();

	shader->SetVector("TextColor", Vector4f(textColor.Red, textColor.Green, textColor.Blue, textColor.Alpha));

	return shader;
}