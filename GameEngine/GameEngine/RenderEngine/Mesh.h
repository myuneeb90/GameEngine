#ifndef MESH_H
#define MESH_H

struct VertexFormat
{
	Vector3f Vertex;
	Vector2f Texcoord;
	Vector3f Normal;
	Vector3f Tangent;
	Vector3f Binormal;
};

struct Mesh
{
	VertexFormat *VertexBuffer;
	unsigned long *IndexBuffer;
	int VertexCount;
	int IndexCount;
};

/*
class Mesh
{
	public:
			VertexFormat *VertexData;
			unsigned long *IndexData;
			EList<Material> *MaterialData;
			int VertexCount;
			int IndexCount;
			int MaterialCount;
	public:
			Mesh();
			~Mesh();

			void CalculateTangentBinormal(VertexFormat v1, VertexFormat v2, VertexFormat v3, Vector3f &tangent, Vector3f &binormal);
			void CalculateTangentBinormal(Vector3f v1, Vector3f v2, Vector3f v3, Vector2f t1, Vector2f t2, Vector2f t3, Vector3f &tangent, Vector3f &binormal);			
			void CalculateNormal(Vector3f &tangent, Vector3f &binormal, Vector3f &normal);
};

*/
#endif