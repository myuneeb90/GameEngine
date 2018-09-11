#include "CoreEngine/AppMain.h"

MeshFilter::MeshFilter()
{
	VertexBuffer = NULL;
	IndexBuffer = NULL;
    Stride = 0;
	Offset = 0;
}

MeshFilter::~MeshFilter()
{
	if(IndexBuffer)
	{
		IndexBuffer->Release();
		IndexBuffer = NULL;
	}

	if(VertexBuffer)
	{
		VertexBuffer->Release();
		VertexBuffer = NULL;
	}

    Stride = 0;
	Offset = 0;
}

void MeshFilter::Construct(Mesh *meshData)
{
	// Vertex Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexResourceData;

	Stride = sizeof(VertexFormat);

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexFormat) * meshData->VertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexResourceData.pSysMem = meshData->VertexBuffer;
	vertexResourceData.SysMemPitch = 0;
	vertexResourceData.SysMemSlicePitch = 0;

	if(FAILED(GlobalRefs::Graphics->Device->CreateBuffer(&vertexBufferDesc, &vertexResourceData, &VertexBuffer)))
	{
		DISPLAY_MESSAGE(L"ERROR", L"Error failed to create Vertex Buffer");
		return;
	}

	// Index Buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA indexResourceData;

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * meshData->IndexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexResourceData.pSysMem = meshData->IndexBuffer;
	indexResourceData.SysMemPitch = 0;
	indexResourceData.SysMemSlicePitch = 0;

	if(FAILED(GlobalRefs::Graphics->Device->CreateBuffer(&indexBufferDesc, &indexResourceData, &IndexBuffer)))
	{
		DISPLAY_MESSAGE(L"ERROR", L"Error failed to create Index Buffer");
		return;		
	}

	MeshData = meshData;

	return;
}

Mesh* MeshFilter::GetMesh()
{
	return MeshData;
}