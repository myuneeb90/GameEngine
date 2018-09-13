#ifndef COMPONENT_H
#define COMPONENT_H

enum RotationType
{
	RT_EULER = 0,
	RT_QUATERNION = 1
};

enum ComponentIDType
{
	CIT_BASE = 0,
	CIT_TRANSFORM = 1,
	CIT_RENDER = 2
};

struct BaseComponent
{
   int ID;
   int EID;
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
	Quaternion RotationQ;
	Vector3f Scale;
	RotationType RotType;
	Matrix4x4f WorldMatrix;

	TransformComponent()
	{
		Position = Vector3f(0, 0, 0);
		Rotation = Vector3f(0, 0, 0);
		RotationQ = Quaternion(0, 0, 0, 1);
		Scale    = Vector3f(1, 1, 1);
		Type = CIT_TRANSFORM;
		RotType = RT_EULER;
		WorldMatrix.Identity();
	}

	TransformComponent(Vector3f position, Vector3f rotation, Vector3f scale)
	{
		Position = position;
		Rotation = rotation;
		RotationQ = Quaternion(0, 0, 0, 1);
		Scale = scale;
		Type = CIT_TRANSFORM;
		RotType = RT_EULER;
		WorldMatrix.Identity();
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