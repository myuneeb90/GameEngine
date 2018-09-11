#ifndef MESH_FILTER_H
#define MESH_FILTER_H

class MeshFilter
{
	private:
			ID3D11Buffer *VertexBuffer;
			ID3D11Buffer *IndexBuffer;
			unsigned int Stride;
			unsigned int Offset;
			Mesh *MeshData;		
	public:
			MeshFilter();
			~MeshFilter();

			void Construct(Mesh *meshData);
			Mesh* GetMesh();			
};

#endif