#ifndef COMPONENT_H
#define COMPONENT_H

enum ComponentIDType
{
	CIT_BASE = 0,
	CIT_TRANSFORM = 1,
	CIT_RENDER = 2
};

struct BaseComponent
{
   int ID;
   ComponentIDType Type;

   BaseComponent()
   {
	   Type = CIT_BASE;
   }
};

struct TransformComponent : public BaseComponent
{
	Vector3f Position;
	Vector3f Rotation;
	Vector3f Scale;

	TransformComponent()
	{
		Position = Vector3f(0, 0, 0);
		Rotation = Vector3f(0, 0, 0);
		Scale    = Vector3f(1, 1, 1);
		Type = CIT_TRANSFORM;
	}

	TransformComponent(Vector3f position, Vector3f rotation, Vector3f scale)
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
		Type = CIT_TRANSFORM;
	}
};

struct RenderComponent : public BaseComponent
{
	Mesh *MeshData;
	Material *MaterialData;

	RenderComponent()
	{
		MeshData = NULL;
		MaterialData = NULL;
		Type = CIT_RENDER;
	}

	RenderComponent(Mesh *meshData, Material *materialData)
	{
		MeshData = meshData;
		MaterialData = materialData;
		Type = CIT_RENDER;
	}
};

#endif