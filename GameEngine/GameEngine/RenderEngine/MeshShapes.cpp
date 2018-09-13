#include "CoreEngine/AppMain.h"

Mesh* MeshShapes::CreateQuad(float size)
{
	float halfSize = size / 2;

	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = 4;
	newMesh->IndexCount = 6;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	newMesh->VertexData[0].Vertex = Vector3f(-halfSize,  halfSize, 0.0f); // Top Left
	newMesh->VertexData[1].Vertex = Vector3f( halfSize,  halfSize, 0.0f); // Top Right
	newMesh->VertexData[2].Vertex = Vector3f( halfSize, -halfSize, 0.0f); // Bottom Right
	newMesh->VertexData[3].Vertex = Vector3f(-halfSize, -halfSize, 0.0f); // Bottom Left
		
	newMesh->VertexData[0].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[1].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[2].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[3].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[0].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[1].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[2].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[3].Normal = Vector3f(0.0f, 0.0f, -1.0f);
									  
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[0], newMesh->VertexData[1], newMesh->VertexData[3], 
	//								  newMesh->VertexData[0].Tangent, newMesh->VertexData[0].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[1], newMesh->VertexData[0], newMesh->VertexData[2], 
	//								  newMesh->VertexData[1].Tangent, newMesh->VertexData[1].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[2], newMesh->VertexData[1], newMesh->VertexData[3], 
	//								  newMesh->VertexData[2].Tangent, newMesh->VertexData[2].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[3], newMesh->VertexData[2], newMesh->VertexData[0], 
	//								  newMesh->VertexData[3].Tangent, newMesh->VertexData[3].Binormal);

	//for(int i = 0; i < newMesh->VertexCount; i++)
	//{
	//	MeshShapes::CalculateNormal(newMesh->VertexData[i].Tangent, newMesh->VertexData[i].Binormal, newMesh->VertexData[i].Normal);
	//}

	// clock wise vertex winding order
	newMesh->IndexData[0] = 0; // Top Left
	newMesh->IndexData[1] = 1; // Top Right
	newMesh->IndexData[2] = 2; // Bottom Right

	newMesh->IndexData[3] = 0; // Top Left
	newMesh->IndexData[4] = 2; // Bottom Right
	newMesh->IndexData[5] = 3; // Bottom Left

	return newMesh;
}

// Add Tangent and Binormal calculations
Mesh* MeshShapes::CreateCircle(float radius, int sides)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = sides * 3;
	newMesh->IndexCount = sides * 3;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	float angle = 360 / (float)sides;
	
	Vector3f centerVertex = Vector3f(0, 0, 0);

	for(int i = 0, j = 0, k = 0; i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vY = 0;

		// Vertex v0
		newMesh->VertexData[j].Vertex = centerVertex;
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(cosAngle, sinAngle);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v2
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = radius * cosAngle;
		vY = radius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(cosAngle, sinAngle);
		newMesh->IndexData[j] = j;
		j++;

		// Vertex v1
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = radius * cosAngle;
		vY = radius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(cosAngle, sinAngle);
		newMesh->IndexData[j] = j;
		j++;		

		// Not tested, placeholder calculations...
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k], newMesh->VertexData[k + 1], newMesh->VertexData[k + 2], 
		//								  newMesh->VertexData[k].Tangent, newMesh->VertexData[k].Binormal);
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k + 1], newMesh->VertexData[k], newMesh->VertexData[k + 2], 
		//								  newMesh->VertexData[k + 1].Tangent, newMesh->VertexData[k + 1].Binormal);
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k + 2], newMesh->VertexData[k + 1], newMesh->VertexData[k], 
		//								  newMesh->VertexData[k + 2].Tangent, newMesh->VertexData[k + 2].Binormal);
		k += 3;
	}

	return newMesh;
}

// Add Tangent and Binormal calculations
Mesh* MeshShapes::CreateRing(float outerRadius, float innerRadius, int sides)
{
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = sides * 4;
	newMesh->IndexCount = sides * 6;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	float angle = 360 / (float)sides;
	
	Vector3f centerVertex = Vector3f(0, 0, 0);

	for(int i = 0, j = 0, k = 0; i < sides; i++)
	{
		float cosAngle = 0, sinAngle = 0, vX = 0, vY = 0;

		// Vertex v0
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = outerRadius * cosAngle;
		vY = outerRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(1, 0);
		j++;

		// Vertex v1
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = outerRadius * cosAngle;
		vY = outerRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(0, 0);
		j++;

		// Vertex v2
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 1)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 1)));

		vX = innerRadius * cosAngle;
		vY = innerRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(1, 1);
		j++;

		// Vertex v3
		cosAngle = cos(Mathf::DegreeToRadian(angle * (i + 2)));
		sinAngle = sin(Mathf::DegreeToRadian(angle * (i + 2)));

		vX = innerRadius * cosAngle;
		vY = innerRadius * sinAngle;

		newMesh->VertexData[j].Vertex = Vector3f(vX, vY, 0);
		newMesh->VertexData[j].Normal = Vector3f(0, 0, -1);
		newMesh->VertexData[j].Texcoord = Vector2f(0, 1);
		j++;	

		// Not tested, placeholder calculations...
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k], newMesh->VertexData[k + 1], newMesh->VertexData[k + 2], 
		//								  newMesh->VertexData[k].Tangent, newMesh->VertexData[k].Binormal);
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k + 1], newMesh->VertexData[k], newMesh->VertexData[k + 2], 
		//								  newMesh->VertexData[k + 1].Tangent, newMesh->VertexData[k + 1].Binormal);
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k + 2], newMesh->VertexData[k + 1], newMesh->VertexData[k], 
		//								  newMesh->VertexData[k + 2].Tangent, newMesh->VertexData[k + 2].Binormal);
		//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[k + 3], newMesh->VertexData[k + 1], newMesh->VertexData[k], 
		//								  newMesh->VertexData[k + 3].Tangent, newMesh->VertexData[k + 3].Binormal);
		k += 4;
	}

	for(int i = 0, j = 0, k = 0; i < sides; i++)
	{
		// Triangle 1
		newMesh->IndexData[j] = k;
		j++;
		newMesh->IndexData[j] = k + 2;
		j++;
		newMesh->IndexData[j] = k + 1;
		j++;

		// Triangle 2
		newMesh->IndexData[j] = k + 2;
		j++;
		newMesh->IndexData[j] = k + 3;
		j++;
		newMesh->IndexData[j] = k + 1;
		j++;

		k += 4;
	}

	return newMesh;
}


Mesh* MeshShapes::CreateCube(float size)
{
	float halfSize = size / 2;

	Mesh *newMesh = NULL;

	newMesh = new Mesh();

	newMesh->VertexCount = 24;
	newMesh->IndexCount = 36;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	// Top Face
	newMesh->VertexData[0].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[1].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[2].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[3].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	
	newMesh->VertexData[0].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[1].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[2].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[3].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[0].Normal = Vector3f(0.0f, 1.0f, 0.0f);
	newMesh->VertexData[1].Normal = Vector3f(0.0f, 1.0f, 0.0f);
	newMesh->VertexData[2].Normal = Vector3f(0.0f, 1.0f, 0.0f);
	newMesh->VertexData[3].Normal = Vector3f(0.0f, 1.0f, 0.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[0], newMesh->VertexData[1], newMesh->VertexData[3], 
	//								  newMesh->VertexData[0].Tangent, newMesh->VertexData[0].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[1], newMesh->VertexData[0], newMesh->VertexData[2], 
	//								  newMesh->VertexData[1].Tangent, newMesh->VertexData[1].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[2], newMesh->VertexData[1], newMesh->VertexData[3], 
	//								  newMesh->VertexData[2].Tangent, newMesh->VertexData[2].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[3], newMesh->VertexData[2], newMesh->VertexData[0], 
	//								  newMesh->VertexData[3].Tangent, newMesh->VertexData[3].Binormal);
									  
	// clock wise vertex winding order
	newMesh->IndexData[0] = 0; 
	newMesh->IndexData[1] = 1; 
	newMesh->IndexData[2] = 2; 

	newMesh->IndexData[3] = 0; 
	newMesh->IndexData[4] = 2; 
	newMesh->IndexData[5] = 3; 

	// Bottom Face
	newMesh->VertexData[4].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[5].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[6].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[7].Vertex = Vector3f(-halfSize, -halfSize, -halfSize);

	newMesh->VertexData[4].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[5].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[6].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[7].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[4].Normal = Vector3f(0.0f, -1.0f, 0.0f);
	newMesh->VertexData[5].Normal = Vector3f(0.0f, -1.0f, 0.0f);
	newMesh->VertexData[6].Normal = Vector3f(0.0f, -1.0f, 0.0f);
	newMesh->VertexData[7].Normal = Vector3f(0.0f, -1.0f, 0.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[4], newMesh->VertexData[5], newMesh->VertexData[7], 
	//								  newMesh->VertexData[4].Tangent, newMesh->VertexData[4].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[5], newMesh->VertexData[4], newMesh->VertexData[6], 
	//								  newMesh->VertexData[5].Tangent, newMesh->VertexData[5].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[6], newMesh->VertexData[5], newMesh->VertexData[7], 
	//								  newMesh->VertexData[6].Tangent, newMesh->VertexData[6].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[7], newMesh->VertexData[6], newMesh->VertexData[4], 
	//								  newMesh->VertexData[7].Tangent, newMesh->VertexData[7].Binormal);

	// anti clock wise vertex winding order
	newMesh->IndexData[6] = 4; 
	newMesh->IndexData[7] = 7; 
	newMesh->IndexData[8] = 6; 

	newMesh->IndexData[9] = 4; 
	newMesh->IndexData[10] = 6; 
	newMesh->IndexData[11] = 5; 

	// Right Face
	newMesh->VertexData[8].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[9].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[10].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[11].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 

	newMesh->VertexData[8].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[9].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[10].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[11].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[8].Normal = Vector3f(1.0f, 0.0f, 0.0f);
	newMesh->VertexData[9].Normal = Vector3f(1.0f, 0.0f, 0.0f);
	newMesh->VertexData[10].Normal = Vector3f(1.0f, 0.0f, 0.0f);
	newMesh->VertexData[11].Normal = Vector3f(1.0f, 0.0f, 0.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[8], newMesh->VertexData[9], newMesh->VertexData[11], 
	//								  newMesh->VertexData[8].Tangent, newMesh->VertexData[8].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[9], newMesh->VertexData[8], newMesh->VertexData[10], 
	//								  newMesh->VertexData[9].Tangent, newMesh->VertexData[9].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[10], newMesh->VertexData[9], newMesh->VertexData[11], 
	//								  newMesh->VertexData[10].Tangent, newMesh->VertexData[10].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[11], newMesh->VertexData[10], newMesh->VertexData[8], 
	//								  newMesh->VertexData[11].Tangent, newMesh->VertexData[11].Binormal);

	// clock wise vertex winding order
	newMesh->IndexData[12] = 8; 
	newMesh->IndexData[13] = 9; 
	newMesh->IndexData[14] = 10; 

	newMesh->IndexData[15] = 8; 
	newMesh->IndexData[16] = 10; 
	newMesh->IndexData[17] = 11; 

	// Left Face
	newMesh->VertexData[12].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[13].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[14].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[15].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 

	newMesh->VertexData[12].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[13].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[14].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[15].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[12].Normal = Vector3f(-1.0f, 0.0f, 0.0f);
	newMesh->VertexData[13].Normal = Vector3f(-1.0f, 0.0f, 0.0f);
	newMesh->VertexData[14].Normal = Vector3f(-1.0f, 0.0f, 0.0f);
	newMesh->VertexData[15].Normal = Vector3f(-1.0f, 0.0f, 0.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[12], newMesh->VertexData[13], newMesh->VertexData[15], 
	//								  newMesh->VertexData[12].Tangent, newMesh->VertexData[12].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[13], newMesh->VertexData[12], newMesh->VertexData[14], 
	//								  newMesh->VertexData[13].Tangent, newMesh->VertexData[13].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[14], newMesh->VertexData[13], newMesh->VertexData[15], 
	//								  newMesh->VertexData[14].Tangent, newMesh->VertexData[14].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[15], newMesh->VertexData[14], newMesh->VertexData[12], 
	//								  newMesh->VertexData[15].Tangent, newMesh->VertexData[15].Binormal);

	// anti clock wise vertex winding order
	newMesh->IndexData[18] = 12; 
	newMesh->IndexData[19] = 15; 
	newMesh->IndexData[20] = 14; 

	newMesh->IndexData[21] = 12; 
	newMesh->IndexData[22] = 14; 
	newMesh->IndexData[23] = 13; 

	// Front Face
	newMesh->VertexData[16].Vertex = Vector3f(-halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[17].Vertex = Vector3f( halfSize,  halfSize,  halfSize); 
	newMesh->VertexData[18].Vertex = Vector3f( halfSize, -halfSize,  halfSize); 
	newMesh->VertexData[19].Vertex = Vector3f(-halfSize, -halfSize,  halfSize); 

	newMesh->VertexData[16].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[17].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[18].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[19].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[16].Normal = Vector3f(0.0f, 0.0f, 1.0f);
	newMesh->VertexData[17].Normal = Vector3f(0.0f, 0.0f, 1.0f);
	newMesh->VertexData[18].Normal = Vector3f(0.0f, 0.0f, 1.0f);
	newMesh->VertexData[19].Normal = Vector3f(0.0f, 0.0f, 1.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[16], newMesh->VertexData[17], newMesh->VertexData[19], 
	//								  newMesh->VertexData[16].Tangent, newMesh->VertexData[16].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[17], newMesh->VertexData[16], newMesh->VertexData[18], 
	//								  newMesh->VertexData[17].Tangent, newMesh->VertexData[17].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[18], newMesh->VertexData[17], newMesh->VertexData[19], 
	//								  newMesh->VertexData[18].Tangent, newMesh->VertexData[18].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[19], newMesh->VertexData[18], newMesh->VertexData[16], 
	//								  newMesh->VertexData[19].Tangent, newMesh->VertexData[19].Binormal);

	// anti clock wise vertex winding order
	newMesh->IndexData[24] = 16; 
	newMesh->IndexData[25] = 19; 
	newMesh->IndexData[26] = 18; 

	newMesh->IndexData[27] = 16; 
	newMesh->IndexData[28] = 18; 
	newMesh->IndexData[29] = 17; 

	// Back Face
	newMesh->VertexData[20].Vertex = Vector3f(-halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[21].Vertex = Vector3f( halfSize,  halfSize, -halfSize); 
	newMesh->VertexData[22].Vertex = Vector3f( halfSize, -halfSize, -halfSize); 
	newMesh->VertexData[23].Vertex = Vector3f(-halfSize, -halfSize, -halfSize); 

	newMesh->VertexData[20].Texcoord = Vector2f(0.0f, 0.0f);
	newMesh->VertexData[21].Texcoord = Vector2f(1.0f, 0.0f);
	newMesh->VertexData[22].Texcoord = Vector2f(1.0f, 1.0f);
	newMesh->VertexData[23].Texcoord = Vector2f(0.0f, 1.0f);

	newMesh->VertexData[20].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[21].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[22].Normal = Vector3f(0.0f, 0.0f, -1.0f);
	newMesh->VertexData[23].Normal = Vector3f(0.0f, 0.0f, -1.0f);

	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[20], newMesh->VertexData[21], newMesh->VertexData[23], 
	//								  newMesh->VertexData[20].Tangent, newMesh->VertexData[20].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[21], newMesh->VertexData[20], newMesh->VertexData[22], 
	//								  newMesh->VertexData[21].Tangent, newMesh->VertexData[21].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[22], newMesh->VertexData[21], newMesh->VertexData[23], 
	//								  newMesh->VertexData[22].Tangent, newMesh->VertexData[22].Binormal);
	//MeshShapes::CalculateTangentBinormal(newMesh->VertexData[23], newMesh->VertexData[22], newMesh->VertexData[20], 
	//								  newMesh->VertexData[23].Tangent, newMesh->VertexData[23].Binormal);

	// clock wise vertex winding order
	newMesh->IndexData[30] = 20; 
	newMesh->IndexData[31] = 21; 
	newMesh->IndexData[32] = 22; 

	newMesh->IndexData[33] = 20; 
	newMesh->IndexData[34] = 22; 
	newMesh->IndexData[35] = 23; 

	return newMesh;
}

Mesh* MeshShapes::CreateCylinder(float bottomRadius, float topRadius, float height, int sliceCount, int stackCount)
{
	vector<VertexFormat> VertexDataContainer;
	vector<unsigned long> IndexDataContainer;

	// Calculate Cylinder Sides
	float stackHeight = height / (float)stackCount;
	float radiusStep = (topRadius - bottomRadius) / (float)stackCount;
	int ringCount = stackCount + 1;

	for(int i = 0; i < ringCount; i++)
	{
		float y = -0.5f * height + i * stackHeight;
		float r = bottomRadius + i * radiusStep;
		float dTheta = 2.0f * Mathf::PI / sliceCount;

		for(int j = 0; j <= sliceCount; j++)
		{
			float cosAngle = cos(j * dTheta);
			float sinAngle = sin(j * dTheta);
			float dr = bottomRadius - topRadius;

			VertexFormat newVertex;

			newVertex.Vertex = Vector3f(r * cosAngle, y, r * sinAngle);
			newVertex.Texcoord = Vector2f((float)j / sliceCount, 1.0f - (float)i / stackCount);
			//newVertex.Tangent = Vector3f(-sinAngle, 0.0f, cosAngle);
			//newVertex.Binormal = Vector3f(dr * cosAngle, -height, dr * sinAngle);
			//newVertex.Normal = Vector3f::Cross(newVertex.Tangent, newVertex.Binormal);
			//newVertex.Normal.Normalize();

			VertexDataContainer.push_back(newVertex);
		}
	}

	int ringVertexCount = sliceCount + 1;

	for(int i = 0; i < stackCount; i++)
	{
		for(int j = 0; j < sliceCount; j++)
		{
			IndexDataContainer.push_back(i * ringVertexCount + j);
			IndexDataContainer.push_back((i + 1) * ringVertexCount + j);
			IndexDataContainer.push_back((i + 1) * ringVertexCount + j + 1);

			IndexDataContainer.push_back(i * ringVertexCount + j);
			IndexDataContainer.push_back((i + 1) * ringVertexCount + j + 1);
			IndexDataContainer.push_back(i * ringVertexCount + j + 1);
		}
	}

	// Calculate Top Cap
	int baseIndex = VertexDataContainer.size();
	float y = 0.5f * height;
	float dTheta = 2.0f * Mathf::PI / sliceCount;

	for(int i = 0; i <= sliceCount; i++)
	{
		VertexFormat newVertex;

		newVertex.Vertex = Vector3f(topRadius * cos(i * dTheta), y, topRadius * sin(i * dTheta));
		newVertex.Texcoord = Vector2f(newVertex.Vertex.X / height + 0.5f, newVertex.Vertex.Z / height + 0.5f);
		newVertex.Normal = Vector3f(0, 1, 0);
		//newVertex.Tangent = Vector3f(1, 0, 0);
		//newVertex.Binormal = Vector3f(0, 0, 1);

		VertexDataContainer.push_back(newVertex);
	}

	VertexFormat newVertex;

	newVertex.Vertex = Vector3f(0, y, 0);
	newVertex.Texcoord = Vector2f(0.5f, 0.5f);
	newVertex.Normal = Vector3f(0, 1, 0);
	//newVertex.Tangent = Vector3f(1, 0, 0);
	//newVertex.Binormal = Vector3f(0, 0, 1);

	VertexDataContainer.push_back(newVertex);
	int centerIndex = VertexDataContainer.size() - 1;

	for(int i = 0; i < sliceCount; i++)
	{
		IndexDataContainer.push_back(centerIndex);
		IndexDataContainer.push_back(baseIndex + i + 1);
		IndexDataContainer.push_back(baseIndex + i);
	}

	// Calculate Bottom Cap
	baseIndex = VertexDataContainer.size();
	y = -0.5f * height;
	dTheta = 2.0f * Mathf::PI / sliceCount;

	for(int i = 0; i <= sliceCount; i++)
	{
		VertexFormat newVertex;

		newVertex.Vertex = Vector3f(bottomRadius * cos(i * dTheta), y, bottomRadius * sin(i * dTheta));
		newVertex.Texcoord = Vector2f(newVertex.Vertex.X / height + 0.5f, newVertex.Vertex.Z / height + 0.5f);
		newVertex.Normal = Vector3f(0, -1, 0);
		//newVertex.Tangent = Vector3f(1, 0, 0);
		//newVertex.Binormal = Vector3f(0, 0, 1);

		VertexDataContainer.push_back(newVertex);
	}

	newVertex.Vertex = Vector3f(0, y, 0);
	newVertex.Texcoord = Vector2f(0.5f, 0.5f);
	newVertex.Normal = Vector3f(0, -1, 0);
	//newVertex.Tangent = Vector3f(1, 0, 0);
	//newVertex.Binormal = Vector3f(0, 0, 1);

	VertexDataContainer.push_back(newVertex);
	centerIndex = VertexDataContainer.size() - 1;

	for(int i = 0; i < sliceCount; i++)
	{
		IndexDataContainer.push_back(centerIndex);
		IndexDataContainer.push_back(baseIndex + i);
		IndexDataContainer.push_back(baseIndex + i + 1);
	}

	// Assign Data To Mesh
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = VertexDataContainer.size();
	newMesh->IndexCount = IndexDataContainer.size();

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	for(int i = 0; i < newMesh->VertexCount; i++)
	{
		newMesh->VertexData[i].Vertex = VertexDataContainer[i].Vertex;
		newMesh->VertexData[i].Texcoord = VertexDataContainer[i].Texcoord;
		newMesh->VertexData[i].Normal = VertexDataContainer[i].Normal;
		//newMesh->VertexData[i].Tangent = VertexDataContainer[i].Tangent;
		//newMesh->VertexData[i].Binormal = VertexDataContainer[i].Binormal;
	}

	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexData[i] = IndexDataContainer[i];
	}

	VertexDataContainer.clear();
	IndexDataContainer.clear();

	return newMesh;
}

Mesh* MeshShapes::CreateGrid(float size, int divisions, float height)
{
	float edgeLength = size / divisions;
	float halfSize = size / 2;
	int divisionPlusOne = divisions + 1;

	Mesh *newMesh = NULL;

	newMesh = new Mesh();

	newMesh->VertexCount = divisionPlusOne * divisionPlusOne;
	newMesh->IndexCount = (divisions / 2) * (divisions / 2) * 24;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	VertexFormat v1, v2, v3;

	// Calculate Vertex Data
	for(int z = 0; z < divisionPlusOne; z++)
	{
		for(int x = 0; x < divisionPlusOne; x++)
		{
			int vtxIdx = x + z * divisionPlusOne;

			newMesh->VertexData[vtxIdx].Vertex = Vector3f(-halfSize + edgeLength * x, height, halfSize - edgeLength * z);
			newMesh->VertexData[vtxIdx].Texcoord = Vector2f((float)x / (float)divisions, (float)z / (float)divisions);
			newMesh->VertexData[vtxIdx].Normal = Vector3f(0, 1, 0);

			v1.Vertex = newMesh->VertexData[vtxIdx].Vertex;
			v2.Vertex = Vector3f(-halfSize + edgeLength * (x + 1), height, halfSize - edgeLength * z);
			v3.Vertex = Vector3f(-halfSize + edgeLength * x, height, halfSize - edgeLength * (z + 1));

			v1.Texcoord = newMesh->VertexData[vtxIdx].Texcoord;
			v2.Texcoord = Vector2f((float)(x + 1) / (float)divisions, (float)z / (float)divisions);
			v3.Texcoord = Vector2f((float)x / (float)divisions, (float)(z + 1) / (float)divisions);

			//MeshShapes::CalculateTangentBinormal(v1, v2, v3, newMesh->VertexData[vtxIdx].Tangent, newMesh->VertexData[vtxIdx].Binormal);		
			//MeshShapes::CalculateNormal(newMesh->VertexData[vtxIdx].Tangent, newMesh->VertexData[vtxIdx].Binormal, newMesh->VertexData[vtxIdx].Normal);
		}
	}

	// Calculate Index Data
	int idx00, idx10, idx20, idx01, idx11, idx21, idx02, idx12, idx22;
	int incrementLimit = 2;
	int halfIncrementLimit = 1;	
	int iCount = 0;

	for(int z = 0; z < divisions; z = z + incrementLimit)
	{
		for(int x = 0; x < divisions; x = x + incrementLimit)
		{
			idx00 = (x + z * (divisionPlusOne));
			idx10 = ((x + halfIncrementLimit) + z * (divisionPlusOne));
			idx20 = ((x + incrementLimit) + z * (divisionPlusOne));
				
			idx01 = (x + (z + halfIncrementLimit) * (divisionPlusOne));
			idx11 = ((x + halfIncrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne));
			idx21 = ((x + incrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne));
				
			idx02 = (x + (z + incrementLimit) * (divisionPlusOne));
			idx12 = ((x + halfIncrementLimit) +  (z + incrementLimit) * (divisionPlusOne));
			idx22 = ((x + incrementLimit) + (z + incrementLimit) * (divisionPlusOne));

			newMesh->IndexData[iCount] = idx00;
			newMesh->IndexData[iCount + 1] = idx10;
			newMesh->IndexData[iCount + 2] = idx11;

			newMesh->IndexData[iCount + 3] = idx00;
			newMesh->IndexData[iCount + 4] = idx11;
			newMesh->IndexData[iCount + 5] = idx01;

			newMesh->IndexData[iCount + 6] = idx10;
			newMesh->IndexData[iCount + 7] = idx20;
			newMesh->IndexData[iCount + 8] = idx11;

			newMesh->IndexData[iCount + 9] = idx20;
			newMesh->IndexData[iCount + 10] = idx21;
			newMesh->IndexData[iCount + 11] = idx11;

			newMesh->IndexData[iCount + 12] = idx01;
			newMesh->IndexData[iCount + 13] = idx11;
			newMesh->IndexData[iCount + 14] = idx02;

			newMesh->IndexData[iCount + 15] = idx02;
			newMesh->IndexData[iCount + 16] = idx11;
			newMesh->IndexData[iCount + 17] = idx12;

			newMesh->IndexData[iCount + 18] = idx11;
			newMesh->IndexData[iCount + 19] = idx22;
			newMesh->IndexData[iCount + 20] = idx12;

			newMesh->IndexData[iCount + 21] = idx11;
			newMesh->IndexData[iCount + 22] = idx21;
			newMesh->IndexData[iCount + 23] = idx22;

			iCount += 24;
		}
	}

	return newMesh;
}

Mesh* MeshShapes::CreateGrid(float size, int divisions, BYTE *heightData, float height)
{
	float edgeLength = size / divisions;
	float halfSize = size / 2;
	int divisionPlusOne = divisions + 1;

	Mesh *newMesh = NULL;

	newMesh = new Mesh();

	newMesh->VertexCount = divisionPlusOne * divisionPlusOne;
	newMesh->IndexCount = (divisions / 2) * (divisions / 2) * 24;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	VertexFormat v1, v2, v3;
	float h1, h2, h3;
	int vtxIdx1 = 0, vtxIdx2 = 0, vtxIdx3 = 0;

	// Calculate Vertex Data
	for(int z = 0; z < divisionPlusOne; z++)
	{
		for(int x = 0; x < divisionPlusOne; x++)
		{
			vtxIdx1 = x + z * divisionPlusOne;
			vtxIdx2 = (x + 1) + z * divisionPlusOne;
			vtxIdx3 = x + (z + 1) * divisionPlusOne;
			
			h1 = (heightData[vtxIdx1] / 256.0f) * height;

			if(x < divisions)
			{
				h2 = (heightData[vtxIdx2] / 256.0f) * height;
			}
			else
			{
				h2 = h1;
			}

			if(z < divisions)
			{
				h3 = (heightData[vtxIdx3] / 256.0f) * height;
			}
			else
			{
				h3 = h1;
			}

			newMesh->VertexData[vtxIdx1].Vertex = Vector3f(-halfSize + edgeLength * x, h1, halfSize - edgeLength * z);
			newMesh->VertexData[vtxIdx1].Texcoord = Vector2f((float)x / (float)divisions, (float)z / (float)divisions);
			newMesh->VertexData[vtxIdx1].Normal = Vector3f(0, 1, 0);

			v1.Vertex = newMesh->VertexData[vtxIdx1].Vertex;
			v2.Vertex = Vector3f(-halfSize + edgeLength * (x + 1), h2, halfSize - edgeLength * z);
			v3.Vertex = Vector3f(-halfSize + edgeLength * x, h3, halfSize - edgeLength * (z + 1));

			v1.Texcoord = newMesh->VertexData[vtxIdx1].Texcoord;
			v2.Texcoord = Vector2f((float)(x + 1) / (float)divisions, (float)z / (float)divisions);
			v3.Texcoord = Vector2f((float)x / (float)divisions, (float)(z + 1) / (float)divisions);

			//MeshShapes::CalculateTangentBinormal(v1, v2, v3, newMesh->VertexData[vtxIdx1].Tangent, newMesh->VertexData[vtxIdx1].Binormal);
			//MeshShapes::CalculateNormal(newMesh->VertexData[vtxIdx1].Tangent, newMesh->VertexData[vtxIdx1].Binormal, newMesh->VertexData[vtxIdx1].Normal);
		}
	}

	int vtxIdx = 0;
	int count = 0;

	// Smooth Out Normals
	for(int z = 0; z < divisionPlusOne; z++)
	{
		for(int x = 0; x < divisionPlusOne; x++)
		{
			Vector3f sum = Vector3f(0, 0, 0);
			count = 0;

			// Bottom Left Normal
			if((x - 1) >= 0 && (z + 1) < (divisionPlusOne))
			{
				vtxIdx = (x - 1) + (z + 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Bottom Right Normal
			if((x + 1) < (divisionPlusOne) && (z + 1) < (divisionPlusOne))
			{
				vtxIdx = (x + 1) + (z + 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Top Left Normal
			if((x - 1) >= 0 && (z - 1) >= 0)
			{
				vtxIdx = (x - 1) + (z - 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Top Right Normal
			if((x + 1) < (divisionPlusOne) && (z - 1) >= 0)
			{
				vtxIdx = (x + 1) + (z - 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Left Normal
			if((x - 1) >= 0)
			{
				vtxIdx = (x - 1) + z * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Right Normal
			if((x + 1) < (divisionPlusOne))
			{
				vtxIdx = (x + 1) + z * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Top Normal
			if((z - 1) >= 0)
			{
				vtxIdx = x + (z - 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Bottom Normal
			if((z + 1) < (divisionPlusOne))
			{
				vtxIdx = x + (z + 1) * (divisionPlusOne);
				sum += newMesh->VertexData[vtxIdx].Normal;
				count++;
			}

			// Take average of the vertices touching this vertex
			sum.X = sum.X / (float)count;
			sum.Y = sum.Y / (float)count;
			sum.Z = sum.Z / (float)count;

			vtxIdx = x + z * (divisionPlusOne);
			newMesh->VertexData[vtxIdx].Normal = sum.Normalize();
		}
	}

	// Calculate Index Data
	int idx00, idx10, idx20, idx01, idx11, idx21, idx02, idx12, idx22;
	int incrementLimit = 2;
	int halfIncrementLimit = 1;	
	int iCount = 0;

	for(int z = 0; z < divisions; z = z + incrementLimit)
	{
		for(int x = 0; x < divisions; x = x + incrementLimit)
		{
			idx00 = (x + z * (divisionPlusOne));
			idx10 = ((x + halfIncrementLimit) + z * (divisionPlusOne));
			idx20 = ((x + incrementLimit) + z * (divisionPlusOne));
				
			idx01 = (x + (z + halfIncrementLimit) * (divisionPlusOne));
			idx11 = ((x + halfIncrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne));
			idx21 = ((x + incrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne));
				
			idx02 = (x + (z + incrementLimit) * (divisionPlusOne));
			idx12 = ((x + halfIncrementLimit) +  (z + incrementLimit) * (divisionPlusOne));
			idx22 = ((x + incrementLimit) + (z + incrementLimit) * (divisionPlusOne));

			newMesh->IndexData[iCount] = idx00;
			newMesh->IndexData[iCount + 1] = idx10;
			newMesh->IndexData[iCount + 2] = idx11;

			newMesh->IndexData[iCount + 3] = idx00;
			newMesh->IndexData[iCount + 4] = idx11;
			newMesh->IndexData[iCount + 5] = idx01;

			newMesh->IndexData[iCount + 6] = idx10;
			newMesh->IndexData[iCount + 7] = idx20;
			newMesh->IndexData[iCount + 8] = idx11;

			newMesh->IndexData[iCount + 9] = idx20;
			newMesh->IndexData[iCount + 10] = idx21;
			newMesh->IndexData[iCount + 11] = idx11;

			newMesh->IndexData[iCount + 12] = idx01;
			newMesh->IndexData[iCount + 13] = idx11;
			newMesh->IndexData[iCount + 14] = idx02;

			newMesh->IndexData[iCount + 15] = idx02;
			newMesh->IndexData[iCount + 16] = idx11;
			newMesh->IndexData[iCount + 17] = idx12;

			newMesh->IndexData[iCount + 18] = idx11;
			newMesh->IndexData[iCount + 19] = idx22;
			newMesh->IndexData[iCount + 20] = idx12;

			newMesh->IndexData[iCount + 21] = idx11;
			newMesh->IndexData[iCount + 22] = idx21;
			newMesh->IndexData[iCount + 23] = idx22;

			iCount += 24;
		}
	}

	return newMesh;
}

Mesh* MeshShapes::CreateSphere(float radius, int divisions)
{
	float edgeLength = 2.0f / divisions;
	float halfSize = 2.0f / 2;
	int divisionPlusOne = divisions + 1;

	Mesh *newMesh = NULL;

	newMesh = new Mesh();

	int perSurfaceVertexCount = (divisionPlusOne * divisionPlusOne);

	newMesh->VertexCount = perSurfaceVertexCount * 6;
	newMesh->IndexCount = ((divisions / 2) * (divisions / 2) * 24) * 6;

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];
	
	Matrix4x4f modelMatrix;

	modelMatrix.Identity();
	
	VertexFormat v1, v2, v3;
	Vector2f tex;
	Vector3f fv;

	// Calculate Vertex Data
	for(int i = 0; i < 6; i++)
	{
		for(int z = 0; z < divisionPlusOne; z++)
		{
			for(int x = 0; x < divisionPlusOne; x++)
			{
				int vtxIdx = (x + z * divisionPlusOne) + (i * perSurfaceVertexCount);

				Vector3f vertex = Vector3f(-halfSize + edgeLength * x, halfSize, halfSize - edgeLength * z);

				if(i == 0) // Top Face
				{
					modelMatrix = Matrix4x4f::RotateZ(0);
				}
				else
				if(i == 1) // Bottom Face
				{	
					modelMatrix = Matrix4x4f::RotateZ(180) * Matrix4x4f::RotateY(180);				
				}
				else
				if(i == 2) // Right Face
				{
					modelMatrix = Matrix4x4f::RotateZ(-90) * Matrix4x4f::RotateY(-90);							
				}
				else
				if(i == 3) // Left Face
				{
					modelMatrix = Matrix4x4f::RotateZ(90) * Matrix4x4f::RotateY(90);						
				}
				else
				if(i == 4) // Front Face
				{
					modelMatrix = Matrix4x4f::RotateX(-90);
				}
				else
				if(i == 5) // Back Face
				{
					modelMatrix = Matrix4x4f::RotateX(90) * Matrix4x4f::RotateY(180);				
				}

				vertex = modelMatrix * vertex;
				Vector3f finalVertex = Mathf::CubeToSphereMapping(vertex);
				newMesh->VertexData[vtxIdx].Vertex = finalVertex * radius;

				v1.Vertex = newMesh->VertexData[vtxIdx].Vertex;
				
				Vector3f _v2;
				_v2 = Vector3f(-halfSize + edgeLength * (x + 1), halfSize, halfSize - edgeLength * z);
				_v2 = modelMatrix * _v2;
				v2.Vertex = Mathf::CubeToSphereMapping(_v2) * radius;

				Vector3f _v3;
				_v3 = Vector3f(-halfSize + edgeLength * x, halfSize, halfSize - edgeLength * (z + 1));
				_v3 = modelMatrix * _v3;
				v3.Vertex = Mathf::CubeToSphereMapping(_v3) * radius;

				newMesh->VertexData[vtxIdx].Texcoord = Vector2f((float)x / (float)divisions, ((float)z / (float)divisions));					
				v1.Texcoord = newMesh->VertexData[vtxIdx].Texcoord;
				v2.Texcoord = Vector2f((float)(x + 1) / (float)divisions, ((float)z / (float)divisions));
				v3.Texcoord = Vector2f((float)x / (float)divisions, ((float)(z + 1) / (float)divisions));

				//MeshShapes::CalculateTangentBinormal(v1, v2, v3, newMesh->VertexData[vtxIdx].Tangent, newMesh->VertexData[vtxIdx].Binormal);
				newMesh->VertexData[vtxIdx].Normal = finalVertex;
			}
		}
	}

	// Calculate Index Data
	int idx00, idx10, idx20, idx01, idx11, idx21, idx02, idx12, idx22;
	int incrementLimit = 2;
	int halfIncrementLimit = 1;	
	int iCount = 0;

	for(int i = 0; i < 6; i++)
	{
		for(int z = 0; z < divisions; z = z + incrementLimit)
		{
			for(int x = 0; x < divisions; x = x + incrementLimit)
			{
				idx00 = (x + z * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx10 = ((x + halfIncrementLimit) + z * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx20 = ((x + incrementLimit) + z * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				
				idx01 = (x + (z + halfIncrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx11 = ((x + halfIncrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx21 = ((x + incrementLimit) + (z + halfIncrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				
				idx02 = (x + (z + incrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx12 = ((x + halfIncrementLimit) +  (z + incrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);
				idx22 = ((x + incrementLimit) + (z + incrementLimit) * (divisionPlusOne)) + (i * perSurfaceVertexCount);

				newMesh->IndexData[iCount] = idx00;
				newMesh->IndexData[iCount + 1] = idx10;
				newMesh->IndexData[iCount + 2] = idx11;

				newMesh->IndexData[iCount + 3] = idx00;
				newMesh->IndexData[iCount + 4] = idx11;
				newMesh->IndexData[iCount + 5] = idx01;

				newMesh->IndexData[iCount + 6] = idx10;
				newMesh->IndexData[iCount + 7] = idx20;
				newMesh->IndexData[iCount + 8] = idx11;

				newMesh->IndexData[iCount + 9] = idx20;
				newMesh->IndexData[iCount + 10] = idx21;
				newMesh->IndexData[iCount + 11] = idx11;

				newMesh->IndexData[iCount + 12] = idx01;
				newMesh->IndexData[iCount + 13] = idx11;
				newMesh->IndexData[iCount + 14] = idx02;

				newMesh->IndexData[iCount + 15] = idx02;
				newMesh->IndexData[iCount + 16] = idx11;
				newMesh->IndexData[iCount + 17] = idx12;

				newMesh->IndexData[iCount + 18] = idx11;
				newMesh->IndexData[iCount + 19] = idx22;
				newMesh->IndexData[iCount + 20] = idx12;

				newMesh->IndexData[iCount + 21] = idx11;
				newMesh->IndexData[iCount + 22] = idx21;
				newMesh->IndexData[iCount + 23] = idx22;

				iCount += 24;
			}
		}
	}

	return newMesh;
}

Mesh* MeshShapes::CreateSphere(float radius, int sliceCount, int stackCount)
{
	vector<VertexFormat> VertexDataContainer;
	vector<unsigned long> IndexDataContainer;

	// Calculate Vertex Data
	VertexFormat topVertex;
	topVertex.Vertex = Vector3f(0, radius, 0);
	topVertex.Texcoord = Vector2f(0.5f, 0);
	topVertex.Normal = Vector3f(0, 1, 0);
	//topVertex.Tangent = Vector3f(1, 0, 0);
	//topVertex.Binormal = Vector3f(0, 0, 1);
	VertexDataContainer.push_back(topVertex);

	float phiStep = Mathf::PI / stackCount;
	float thetaStep = 2.0f * Mathf::PI / sliceCount;

	for(int i = 1; i <= stackCount - 1; i++)
	{
		float phi = (float)i * phiStep;
		
		for(int j = 0; j <= sliceCount; j++)
		{
			float theta = (float)j * thetaStep;

			VertexFormat newVertex;
			
			newVertex.Vertex = Vector3f(radius * sin(phi) * cos(theta),
								        radius * cos(phi),
								        radius * sin(phi) * sin(theta));
			newVertex.Texcoord = Vector2f(theta / (Mathf::PI * 2), phi / Mathf::PI); 
			newVertex.Normal = newVertex.Vertex;
			newVertex.Normal.Normalize();
/*			newVertex.Tangent = Vector3f(-radius * sin(phi) * sin(theta),
										 0,
										 radius * sin(phi) * cos(theta));
			newVertex.Binormal = Vector3f(radius * sin(phi) * sin(theta),
										  0,
										  -radius * sin(phi) * cos(theta));	*/		
			VertexDataContainer.push_back(newVertex);
		}
	}

	VertexFormat bottomVertex;
	bottomVertex.Vertex = Vector3f(0, -radius, 0);
	bottomVertex.Texcoord = Vector2f(0.5f, 1);
	bottomVertex.Normal = Vector3f(0, -1, 0);
	//bottomVertex.Tangent = Vector3f(1, 0, 0);
	//bottomVertex.Binormal = Vector3f(0, 0, 1);
	VertexDataContainer.push_back(bottomVertex);

	// Calculate Index Data
	for(int i = 1; i <= sliceCount; i++)
	{
		IndexDataContainer.push_back(0);
		IndexDataContainer.push_back(i + 1);
		IndexDataContainer.push_back(i);
	}

	int baseIndex = 1;
	int ringVertexCount = sliceCount + 1;

	for(int i = 0; i < stackCount - 2; i++)
	{
		for(int j = 0; j < sliceCount; j++)
		{
			IndexDataContainer.push_back(baseIndex + i * ringVertexCount + j);
			IndexDataContainer.push_back(baseIndex + i * ringVertexCount + j + 1);
			IndexDataContainer.push_back(baseIndex + (i + 1) * ringVertexCount + j);

			IndexDataContainer.push_back(baseIndex + (i + 1) * ringVertexCount + j);
			IndexDataContainer.push_back(baseIndex + i * ringVertexCount + j + 1);
			IndexDataContainer.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
		}
	}

	int southPoleIndex = VertexDataContainer.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;
	
	for(int i = 0; i < sliceCount; i++)
	{
		IndexDataContainer.push_back(southPoleIndex);
		IndexDataContainer.push_back(baseIndex + i);
		IndexDataContainer.push_back(baseIndex + i + 1);
	}

	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = VertexDataContainer.size();
	newMesh->IndexCount = IndexDataContainer.size();

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	for(int i = 0; i < newMesh->VertexCount; i++)
	{
		newMesh->VertexData[i].Vertex = VertexDataContainer[i].Vertex;
		newMesh->VertexData[i].Texcoord = VertexDataContainer[i].Texcoord;
		newMesh->VertexData[i].Normal = VertexDataContainer[i].Normal;
		//newMesh->VertexData[i].Tangent = VertexDataContainer[i].Tangent;
		//newMesh->VertexData[i].Binormal = VertexDataContainer[i].Binormal;
	}

	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexData[i] = IndexDataContainer[i];
	}
	
	VertexDataContainer.clear();
	IndexDataContainer.clear();

	return newMesh;
}

Mesh* MeshShapes::CreateTorus(float outerRadius, float innerRadius, int outerSides, int innerSides)
{
	vector<VertexFormat> VertexDataContainer;
	vector<unsigned long> IndexDataContainer;

	float innerAngleStep = Mathf::DegreeToRadian(360 / (float)innerSides);
	float outerAngleStep = Mathf::DegreeToRadian(360 / (float)outerSides);

	Vector3f vertexCenter;

	float phi = 0;
	float theta = 0;

	for(int i = 0; i < outerSides + 1; i++)
	{
		theta = (i + 1) * outerAngleStep;

		vertexCenter = Vector3f(outerRadius * cos(theta),
							    0,
								outerRadius * sin(theta));

		for(int j = 0; j < innerSides + 1; j++)
		{
			VertexFormat newVertex;

			phi = (j + 1) * innerAngleStep;

			newVertex.Vertex = Vector3f(vertexCenter.X + (innerRadius * sin(phi) * cos(theta)),
										vertexCenter.Y + innerRadius * cos(phi), 
										vertexCenter.Z + (innerRadius * sin(phi) * sin(theta)));
			newVertex.Texcoord = Vector2f((float)j / innerSides, 1.0f - (float)i / outerSides);
			newVertex.Normal = Vector3f((innerRadius * sin(phi) * cos(theta)),
										innerRadius * cos(phi),
										(innerRadius * sin(phi) * sin(theta)));
			newVertex.Normal.Normalize();
			//newVertex.Tangent = Vector3f((innerRadius * sin(phi + Mathf::DegreeToRadian(90)) * cos(theta)),
			//							 innerRadius * cos(phi + Mathf::DegreeToRadian(90)),
			//							(innerRadius * sin(phi + Mathf::DegreeToRadian(90)) * sin(theta)));
			//newVertex.Tangent.Normalize();
			//newVertex.Binormal = Vector3f::Cross(newVertex.Normal, newVertex.Tangent);
			
			VertexDataContainer.push_back(newVertex);
		}
	}

	int ringVertexCount = innerSides + 1;

	for(int i = 0; i < outerSides; i++)
	{
		for(int j = 0; j < innerSides; j++)
		{
			IndexDataContainer.push_back(i * ringVertexCount + j);
			IndexDataContainer.push_back((i + 1) * ringVertexCount + j);
			IndexDataContainer.push_back((i + 1) * ringVertexCount + (j + 1));

			IndexDataContainer.push_back(i * ringVertexCount + j);			
			IndexDataContainer.push_back((i + 1) * ringVertexCount + (j + 1));
			IndexDataContainer.push_back(i * ringVertexCount + (j + 1));
		}
	}

	// Assign Mesh Data
	Mesh *newMesh = new Mesh();

	newMesh->VertexCount = VertexDataContainer.size();
	newMesh->IndexCount = IndexDataContainer.size();

	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];

	for(int i = 0; i < newMesh->VertexCount; i++)
	{
		newMesh->VertexData[i].Vertex = VertexDataContainer[i].Vertex;
		newMesh->VertexData[i].Texcoord = VertexDataContainer[i].Texcoord;
		newMesh->VertexData[i].Normal = VertexDataContainer[i].Normal;
		//newMesh->VertexData[i].Tangent = VertexDataContainer[i].Tangent;
		//newMesh->VertexData[i].Binormal = VertexDataContainer[i].Binormal;
	}

	for(int i = 0; i < newMesh->IndexCount; i++)
	{
		newMesh->IndexData[i] = IndexDataContainer[i];
	}

	VertexDataContainer.clear();
	IndexDataContainer.clear();

	return newMesh;
}
/*
Mesh* MeshShapes::LoadModel(char *fileName)
{
	ifstream modelFile;
	char input;
	int i;
	Mesh *newMesh = new Mesh();

	modelFile.open(fileName);
	// if it could not open then exit
	if(modelFile.fail())
	{
		cout<<"Error model file could not load"<<endl;
		return NULL;
	}

	// read up to the value of vertex count
	modelFile.get(input);
	while(input != ':')
	{
		modelFile.get(input);
	}

	// read in the vertex count;
	modelFile >> newMesh->VertexCount;
	modelFile.get(input);
	while(input != ':')
	{
		modelFile.get(input);
	}
	cout<<input<<endl;
	modelFile >> newMesh->MaterialCount;

	cout<<"Model Loading"<<endl;
	cout<<newMesh->VertexCount<<endl;
	cout<<newMesh->MaterialCount<<endl;

	newMesh->MaterialData = new EList<Material>();

	for(int i = 0; i < newMesh->MaterialCount; i++)
	{
		newMesh->MaterialData->Add(new StandardMaterial(Shaders::CreateDefaultShader(Color(1, 1, 1, 1))));
		string var;
		while(input != ' ')
		{
			modelFile.get(input);
			var += input;
		}
		modelFile >> newMesh->MaterialData->GetNodeData(i)->StartIndex;
		modelFile >> newMesh->MaterialData->GetNodeData(i)->IndexCount;
		modelFile >> newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Red;
		modelFile >> newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Green;
		modelFile >> newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Blue;
		
		cout<<newMesh->MaterialData->GetNodeData(i)->StartIndex<<" : "<<newMesh->MaterialData->GetNodeData(i)->IndexCount<<" : ";
		cout<<newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Red<<" : "<<newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Green<<" : ";
		cout<<newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Blue<<endl;
		modelFile.get(input);

		newMesh->MaterialData->GetNodeData(i)->GetShader()->SetVector("DiffuseColor", Vector4f(newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Red, 
																							   newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Green, 
																							   newMesh->MaterialData->GetNodeData(i)->DiffuseColor.Blue, 1.0f));
		((StandardMaterial*)newMesh->MaterialData->GetNodeData(i))->LoadMainTexture(L"../Endeaverse Engine/Assets/Textures/stone01.dds");
		((StandardMaterial*)newMesh->MaterialData->GetNodeData(i))->CreateSamplerState();
	//	if(i == 1)
	//	newMesh->MaterialData->GetNodeData(i)->GetShader()->SetVector("TextureTile", Vector4f(2, 2, 1, 1));	
	}
	// set the number of indices to be the same as the vertex count
	newMesh->IndexCount = newMesh->VertexCount;

	// Create the model using the vertex count that was read in.
	newMesh->VertexData = new VertexFormat[newMesh->VertexCount];
	newMesh->IndexData = new unsigned long[newMesh->IndexCount];
	// Read up to the beginning of the data.
	modelFile.get(input);
	while(input != ':')
	{
		modelFile.get(input);
	}
	modelFile.get(input);
	modelFile.get(input);

	// read in the vertex data
	for(i = 0; i < newMesh->VertexCount; i++)
	{
		modelFile >> newMesh->VertexData[i].Vertex.X >> newMesh->VertexData[i].Vertex.Y >> newMesh->VertexData[i].Vertex.Z;
		modelFile >> newMesh->VertexData[i].Texcoord.X >> newMesh->VertexData[i].Texcoord.Y;
		modelFile >> newMesh->VertexData[i].Normal.X >> newMesh->VertexData[i].Normal.Y >> newMesh->VertexData[i].Normal.Z;
		newMesh->IndexData[i] = i;
	}

	modelFile.close();

	return newMesh;
}
*/

void MeshShapes::CalculateTangentBinormal(VertexFormat v1, VertexFormat v2, VertexFormat v3, Vector3f &tangent, Vector3f &binormal)
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

void MeshShapes::CalculateTangentBinormal(Vector3f v1, Vector3f v2, Vector3f v3, 
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

void MeshShapes::CalculateNormal(Vector3f &tangent, Vector3f &binormal, Vector3f &normal)
{
	// Calculate the cross product of the tangent and binormal which will give the normal vector.
	normal.X = (tangent.Y * binormal.Z) - (tangent.Z * binormal.Y);
	normal.Y = (tangent.Z * binormal.X) - (tangent.X * binormal.Z);
	normal.Z = (tangent.X * binormal.Y) - (tangent.Y * binormal.X);

	// Normalize the normal
	normal.Normalize();

	return;
}