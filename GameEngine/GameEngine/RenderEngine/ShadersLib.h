#ifndef SHADERS_LIB_H
#define SHADERS_LIB_H

#define SHADERPATH L"../GameEngine/Assets/Shaders/"

class ShadersLib
{
	public:
			static Shader* CreateDefaultShader(Color diffuseColor);
			static Shader* CreateLineShader(Color lineColor);
			static Shader* CreateSpriteShader(Color diffuseColor);
			static Shader* CreateFontShader(Color textColor);
};

#endif