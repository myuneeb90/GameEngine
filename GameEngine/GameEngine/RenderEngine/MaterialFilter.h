#ifndef MATERIAL_FILTER_H
#define MATERIAL_FILTER_H

class MaterialFilter
{
	public:
			Shader *ShaderData;
	
			int StartIndex;
			int IndexCount;
	public:
			MaterialFilter(Shader *shaderData);
			virtual ~MaterialFilter();
};

#endif