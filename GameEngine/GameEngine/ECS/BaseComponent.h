#ifndef COMPONENT_H
#define COMPONENT_H

struct BaseComponent
{
   int ID;
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
	}

	TransformComponent(Vector3f position = Vector3f(0, 0, 0), Vector3f rotation = Vector3f(0, 0, 0), Vector3f scale = Vector3f(1, 1, 1))
	{
		Position = position;
		Rotation = rotation;
		Scale = scale;
	}
};

struct RenderComponent : public BaseComponent
{
	Mesh *MeshData;
	Material *MaterialData;
};

#endif