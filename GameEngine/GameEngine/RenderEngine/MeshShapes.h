#ifndef MESHSHAPES_H
#define MESHSHAPES_H

class MeshShapes
{
	public:

			// Shape Functions
			static Mesh* CreateQuad(float size);
		    static Mesh* CreateCircle(float radius, int sides);
		    static Mesh* CreateRing(float outerRadius, float innerRadius, int sides);
			static Mesh* CreateCube(float size);
			static Mesh* CreateCylinder(float bottomRadius, float topRadius, float height, int sliceCount, int stackCount);
			static Mesh* CreateGrid(float size, int divisions, float height = 0);
			static Mesh* CreateGrid(float size, int divisions, BYTE *heightData, float height);
			static Mesh* CreateSphere(float radius, int divisions);
			static Mesh* CreateSphere(float radius, int sliceCount, int stackCount); 
			static Mesh* CreateTorus(float outerRadius, float innerRadius, int outerSides, int innerSides);
		//	static Mesh* LoadModel(char *fileName);

			static void CalculateTangentBinormal(VertexFormat v1, VertexFormat v2, VertexFormat v3, Vector3f &tangent, Vector3f &binormal);
			static void CalculateTangentBinormal(Vector3f v1, Vector3f v2, Vector3f v3, Vector2f t1, Vector2f t2, Vector2f t3, Vector3f &tangent, Vector3f &binormal);			
			static void CalculateNormal(Vector3f &tangent, Vector3f &binormal, Vector3f &normal);

};

#endif