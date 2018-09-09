#include "CoreEngine/AppMain.h"

/*
Mesh::Mesh()
{
	VertexData = NULL;
	IndexData = NULL;
	MaterialData = NULL;
	VertexCount = 0;
	IndexCount = 0;
	MaterialCount = 0;
}

Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY(VertexData);
	SAFE_DELETE_ARRAY(IndexData);
	SAFE_DELETE(MaterialData);
	VertexCount = 0;
	IndexCount = 0;
	MaterialCount = 0;
}

void Mesh::CalculateTangentBinormal(VertexType v1, VertexType v2, VertexType v3, Vector3f &tangent, Vector3f &binormal)
{
	Vector3f vec1, vec2;
	Vector2f tex1, tex2;
	float denominator;

	// Calculate the two vectors for this face
	vec1 = v2.Vertex - v1.Vertex;
	vec2 = v3.Vertex - v1.Vertex;

	// Calculate tex1 and tex2 texture space vectors
	tex1 = v2.Texcoord - v1.Texcoord;
	tex2 = v3.Texcoord - v1.Texcoord;

	// Calculate the denominator of the tangent / binormal equation
	denominator = 1.0f / (tex1.X * tex2.Y - tex1.Y * tex2.X);

	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
	tangent.X = (tex2.Y * vec1.X - tex2.X * vec2.X) * denominator;
	tangent.Y = (tex2.Y * vec1.Y - tex2.X * vec2.Y) * denominator;
	tangent.Z = (tex2.Y * vec1.Z - tex2.X * vec2.Z) * denominator;

	binormal.X = (tex1.X * vec2.X - tex1.Y * vec1.X) * denominator;
	binormal.Y = (tex1.X * vec2.Y - tex1.Y * vec1.Y) * denominator;
	binormal.Z = (tex1.X * vec2.Z - tex1.Y * vec1.Z) * denominator;

	tangent.Normalize();
	binormal.Normalize();

	return;
}

void Mesh::CalculateTangentBinormal(Vector3f v1, Vector3f v2, Vector3f v3, 
									Vector2f t1, Vector2f t2, Vector2f t3, 
									Vector3f &tangent, Vector3f &binormal)
{
	Vector3f vec1, vec2;
	Vector2f tex1, tex2;
	float denominator;

	// Calculate the two vectors for this face
	vec1 = v2 - v1;
	vec2 = v3 - v1;

	// Calculate tex1 and tex2 texture space vectors
	tex1 = t2 - t1;
	tex2 = t3 - t1;

	// Calculate the denominator of the tangent / binormal equation
	denominator = 1.0f / (tex1.X * tex2.Y - tex1.Y * tex2.X);

	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
	tangent.X = (tex2.Y * vec1.X - tex2.X * vec2.X) * denominator;
	tangent.Y = (tex2.Y * vec1.Y - tex2.X * vec2.Y) * denominator;
	tangent.Z = (tex2.Y * vec1.Z - tex2.X * vec2.Z) * denominator;

	binormal.X = (tex1.X * vec2.X - tex1.Y * vec1.X) * denominator;
	binormal.Y = (tex1.X * vec2.Y - tex1.Y * vec1.Y) * denominator;
	binormal.Z = (tex1.X * vec2.Z - tex1.Y * vec1.Z) * denominator;

	tangent.Normalize();
	binormal.Normalize();
}

void Mesh::CalculateNormal(Vector3f &tangent, Vector3f &binormal, Vector3f &normal)
{
	// Calculate the cross product of the tangent and binormal which will give the normal vector.
	normal.X = (tangent.Y * binormal.Z) - (tangent.Z * binormal.Y);
	normal.Y = (tangent.Z * binormal.X) - (tangent.X * binormal.Z);
	normal.Z = (tangent.X * binormal.Y) - (tangent.Y * binormal.X);

	// Normalize the normal
	normal.Normalize();

	return;
}
*/