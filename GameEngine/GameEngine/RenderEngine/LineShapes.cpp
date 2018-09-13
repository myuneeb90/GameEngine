#include "CoreEngine/AppMain.h"

Mesh* LineShapes::CreateLine(Vector3f point1, Vector3f point2)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 2;
	newMesh->IndexCount = 2;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount]; 

	newMesh->VertexData[0].Vertex = point1;
	newMesh->VertexData[1].Vertex = point2;

	newMesh->IndexData[0] = 0;
	newMesh->IndexData[1] = 1;

	return newMesh;
}

Mesh* LineShapes::CreateQuad(float size)
{
	float halfSize = size / 2;

	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 8;
	newMesh->IndexCount = 8;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	newMesh->VertexData[0].Vertex = Vector3f(-halfSize,  halfSize, 0.0f); // Top Left
	newMesh->VertexData[1].Vertex = Vector3f( halfSize,  halfSize, 0.0f); // Top Right
	newMesh->VertexData[2].Vertex = Vector3f( halfSize,  halfSize, 0.0f); // Top Right
	newMesh->VertexData[3].Vertex = Vector3f( halfSize, -halfSize, 0.0f); // Bottom Right
	newMesh->VertexData[4].Vertex = Vector3f( halfSize, -halfSize, 0.0f); // Bottom Right
	newMesh->VertexData[5].Vertex = Vector3f(-halfSize, -halfSize, 0.0f); // Bottom Left
	newMesh->VertexData[6].Vertex = Vector3f(-halfSize, -halfSize, 0.0f); // Bottom Left
	newMesh->VertexData[7].Vertex = Vector3f(-halfSize,  halfSize, 0.0f); // Top Left
		
	// clock wise vertex winding order
	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexData[i] = i;
	}

	return newMesh;
}

Mesh* LineShapes::CreateCircle(float radius, int sides)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = sides * 2;
	newMesh->IndexCount = sides * 2;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	float angle = 360 / (float)sides;
	
	Vector3f centerVertex = Vector3f(0, 0, 0);

	for(int i = 0, j = 0, k = 0; i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vY = 0;

		// Vertex v1
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = radius * cosAngle;
		vY = radius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = radius * cosAngle;
		vY = radius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->IndexData[j] = j;
		j++;		
	}

	return newMesh;
}

Mesh* LineShapes::CreateCube(float size)
{
	float halfSize = size / 2;

	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 48;
	newMesh->IndexCount = 48;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	// Top Face
	newMesh->VertexData[0].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[1].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[2].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[3].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[4].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[5].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[6].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[7].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 

	// Bottom Face
	newMesh->VertexData[8].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[9].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[10].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[11].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[12].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[13].Vertex = Vector3f(-halfSize, -halfSize, -halfSize);
	newMesh->VertexData[14].Vertex = Vector3f(-halfSize, -halfSize, -halfSize);
	newMesh->VertexData[15].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 

	// Right Face
	newMesh->VertexData[16].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[17].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[18].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[19].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[20].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[21].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[22].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[23].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 

	// Left Face
	newMesh->VertexData[24].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[25].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[26].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[27].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[28].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[29].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[30].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[31].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 

	// Front Face
	newMesh->VertexData[32].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[33].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[34].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[35].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[36].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[37].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[38].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[39].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 

	// Back Face
	newMesh->VertexData[40].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[41].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[42].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[43].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[44].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[45].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[46].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[47].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 

	// clock wise vertex winding order
	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexData[i] = i;
	}

	return newMesh;
}

Mesh* LineShapes::CreateCylinder(float bottomRadius, float topRadius, float height, int sides)
{
	float halfHeight = height / 2;
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = (sides * 2) * 3;
	newMesh->IndexCount = (sides * 2) * 3;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	float angle = 360 / (float)sides;
	Vector3f centerVertex = Vector3f(0, 0, 0);

	// Calculate Top Side
	for(int i = 0, j = 0; i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vZ = 0;

		// Vertex v1
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = topRadius * cosAngle;
		vZ = topRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = topRadius * cosAngle;
		vZ = topRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;		
	}

	// Calculate Bottom Side
	for(int i = 0, j = (sides * 2); i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vZ = 0;

		// Vertex v1
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = bottomRadius * cosAngle;
		vZ = bottomRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = bottomRadius * cosAngle;
		vZ = bottomRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;		
	}

	// Calculate Cylinder Sides
	for(int i = 0, j = (sides * 2) * 2; i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vZ = 0;

		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		// Vertex v1
		vX = topRadius * cosAngle;
		vZ = topRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v0
		vX = bottomRadius * cosAngle;
		vZ = bottomRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexData[j] = j;
		j++;		
	}

	return newMesh;
}
