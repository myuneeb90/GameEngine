#ifndef MATERIAL_FILTER_H
#define MATERIAL_FILTER_H

class MaterialFilter
{
	protected:
			  Shader *ShaderData;
	public:
			int StartIndex;
			int IndexCount;
	public:
			MaterialFilter(Shader *shaderData);
			virtual ~MaterialFilter();

			Shader* GetShader();
};

#endif