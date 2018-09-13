#include "CoreEngine/AppMain.h"

MaterialFilter::MaterialFilter(Shader *shaderData)
{
	ShaderData = shaderData;
	StartIndex = 0;
	IndexCount = 0;
}

MaterialFilter::~MaterialFilter()
{
	SAFE_DELETE(ShaderData);
}