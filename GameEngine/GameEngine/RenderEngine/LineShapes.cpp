#include "CoreEngine/AppMain.h"

Mesh* LineShapes::CreateLine(Vector3f point1, Vector3f point2)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 2;
	newMesh->IndexCount = 2;

	newMesh->VertexBuffer = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexBuffer = new unsigned long[newMesh->IndexCount]; 

	newMesh->VertexBuffer[0].Vertex = point1;
	newMesh->VertexBuffer[1].Vertex = point2;

	newMesh->IndexBuffer[0] = 0;
	newMesh->IndexBuffer[1] = 1;

	return newMesh;
}

Mesh* LineShapes::CreateQuad(float size)
{
	float halfSize = size / 2;

	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 8;
	newMesh->IndexCount = 8;

	newMesh->VertexBuffer = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexBuffer = new unsigned long[newMesh->IndexCount];

	newMesh->VertexBuffer[0].Vertex = Vector3f(-halfSize,  halfSize, 0.0f); // Top Left
	newMesh->VertexBuffer[1].Vertex = Vector3f( halfSize,  halfSize, 0.0f); // Top Right
	newMesh->VertexBuffer[2].Vertex = Vector3f( halfSize,  halfSize, 0.0f); // Top Right
	newMesh->VertexBuffer[3].Vertex = Vector3f( halfSize, -halfSize, 0.0f); // Bottom Right
	newMesh->VertexBuffer[4].Vertex = Vector3f( halfSize, -halfSize, 0.0f); // Bottom Right
	newMesh->VertexBuffer[5].Vertex = Vector3f(-halfSize, -halfSize, 0.0f); // Bottom Left
	newMesh->VertexBuffer[6].Vertex = Vector3f(-halfSize, -halfSize, 0.0f); // Bottom Left
	newMesh->VertexBuffer[7].Vertex = Vector3f(-halfSize,  halfSize, 0.0f); // Top Left
		
	// clock wise vertex winding order
	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexBuffer[i] = i;
	}

	return newMesh;
}

Mesh* LineShapes::CreateCircle(float radius, int sides)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = sides * 2;
	newMesh->IndexCount = sides * 2;

	newMesh->VertexBuffer = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexBuffer = new unsigned long[newMesh->IndexCount];

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

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->IndexBuffer[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = radius * cosAngle;
		vY = radius * sinAngle;

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->IndexBuffer[j] = j;
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

	newMesh->VertexBuffer = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexBuffer = new unsigned long[newMesh->IndexCount];

	// Top Face
	newMesh->VertexBuffer[0].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[1].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[2].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[3].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[4].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[5].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[6].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[7].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 

	// Bottom Face
	newMesh->VertexBuffer[8].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[9].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[10].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[11].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[12].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[13].Vertex = Vector3f(-halfSize, -halfSize, -halfSize);
	newMesh->VertexBuffer[14].Vertex = Vector3f(-halfSize, -halfSize, -halfSize);
	newMesh->VertexBuffer[15].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 

	// Right Face
	newMesh->VertexBuffer[16].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[17].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[18].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[19].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[20].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[21].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[22].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[23].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 

	// Left Face
	newMesh->VertexBuffer[24].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[25].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[26].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[27].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[28].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[29].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[30].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[31].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 

	// Front Face
	newMesh->VertexBuffer[32].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[33].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[34].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexBuffer[35].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[36].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[37].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[38].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexBuffer[39].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 

	// Back Face
	newMesh->VertexBuffer[40].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[41].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[42].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexBuffer[43].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[44].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[45].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[46].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 
	newMesh->VertexBuffer[47].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 

	// clock wise vertex winding order
	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexBuffer[i] = i;
	}

	return newMesh;
}

Mesh* LineShapes::CreateCylinder(float bottomRadius, float topRadius, float height, int sides)
{
	float halfHeight = height / 2;
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = (sides * 2) * 3;
	newMesh->IndexCount = (sides * 2) * 3;

	newMesh->VertexBuffer = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexBuffer = new unsigned long[newMesh->IndexCount];

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

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = topRadius * cosAngle;
		vZ = topRadius * sinAngle;

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
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

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
		j++;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = bottomRadius * cosAngle;
		vZ = bottomRadius * sinAngle;

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
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

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
		j++;

		// Vertex v0
		vX = bottomRadius * cosAngle;
		vZ = bottomRadius * sinAngle;

		newMesh->VertexBuffer[j].Vertex = Vector3f(vX, -halfHeight, vZ);
		newMesh->IndexBuffer[j] = j;
		j++;		
	}

	return newMesh;
}
