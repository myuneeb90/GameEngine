#include "CoreEngine/AppMain.h"

#include <qwidget.h>

RenderSystem::RenderSystem()
{
	Group = NULL;
	TransformList = NULL;
	RenderList = NULL;
	MeshFilterList = NULL;
	MaterialFilterList = NULL;
	RenderCount = 0;

	CamPos = Vector3f(0, 1, -5);
	Velocity = Vector3f(0.0f, 0.0f, 0.0f);
	Up = Vector3f(0, 1, 0);
	Right = Vector3f(1, 0, 0);
	Look = Vector3f(0, 0, 1);
	LookAt = Vector3f(0, 0, 1);
	Speed = 1.1f;
}

RenderSystem::~RenderSystem()
{
	this->Destroy();
}

void RenderSystem::Initialize(EntityPool *pool)
{
	// use the pool to populate this entity group
	Group = new EntityGroup();

	for(int i = 0; i < pool->EntityList->Count; i++)
	{
		for(int j = 0; j < pool->EntityList->GetNodeData(i)->ComponentList->Count; j++)
		{
			if(pool->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j)->Type == CIT_RENDER)
			{
				Group->AddEntity(pool->EntityList->GetNodeData(i));
				break;
			}
		}
	}

	RenderList = new EList<RenderComponent>();
	TransformList = new EList<TransformComponent>();

	for(int i = 0; i < Group->EntityList->Count; i++)
	{
		for(int j = 0; j < Group->EntityList->GetNodeData(i)->ComponentList->Count; j++)
		{
			if(Group->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j)->Type == CIT_TRANSFORM)
			{
				TransformList->Add((TransformComponent*)Group->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j));
			}

			if(Group->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j)->Type == CIT_RENDER)
			{
				RenderList->Add((RenderComponent*)Group->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j));
			}
		}
	}

	RenderCount = RenderList->Count;
	MeshFilterList = new EList<MeshFilter>();
	MaterialFilterList = new EList<MaterialFilter>();

	for(int i = 0; i < RenderList->Count; i++)
	{
		MeshFilter *meshFilter = new MeshFilter();
		meshFilter->Construct(RenderList->GetNodeData(i)->MeshData);
		MeshFilterList->Add(meshFilter);

		MaterialFilter *materialFilter = new MaterialFilter(ShadersLib::CreateDefaultShader(RenderList->GetNodeData(i)->MaterialData->DiffuseColor));
		MaterialFilterList->Add(materialFilter);
	}

	cout<<"W : "<<(float)GlobalRefs::Window->ScreenWidth<<" , H : "<<(float)GlobalRefs::Window->ScreenHeight<<endl;
	this->ConstructPerspectiveMatrix(45.0f, (float)GlobalRefs::Window->ScreenWidth, (float)GlobalRefs::Window->ScreenHeight, 0.1f, 1000);

//	cout<<"Render System Entity Group Count : "<<Group->EntityList->Count<<endl;
}

void RenderSystem::Execute()
{
	// Temp Update
//	Vector3f position = Vector3f(0, 0, 5);
//	Vector3f lookAt = position + Vector3f(0, 0, 1);

//	View = Matrix4x4f::LookAtLH(position, lookAt, Vector3f(0, 1, 0));
	this->FPSTestCam();

	for(int i = 0; i < RenderCount; i++)
	{
		MeshFilter *meshFilter = MeshFilterList->GetNodeData(i);
		MaterialFilter *materialFilter = MaterialFilterList->GetNodeData(i);

		Matrix4x4f world;
		Matrix4x4f wvp;

		//world = TransformList->GetNodeData(i)->WorldMatrix;
		//world.Print();
		world.Identity();
		wvp = world * View * Projection;

	//	wvp.Print();

		materialFilter->ShaderData->SetMatrix("WVP", wvp);
		materialFilter->ShaderData->SetMatrix("World", world);
		
		GlobalRefs::Graphics->DeviceContext->IASetVertexBuffers(0, 1, &meshFilter->VertexBuffer, &meshFilter->Stride, &meshFilter->Offset);
		GlobalRefs::Graphics->DeviceContext->IASetIndexBuffer(meshFilter->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
		GlobalRefs::Graphics->DeviceContext->IASetInputLayout(materialFilter->ShaderData->GetInputLayout());

		if(materialFilter->ShaderData->GetShaderType() == ST_MESH)
		{
			GlobalRefs::Graphics->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//		cout<<"Mesh Render Type"<<endl;
		}
		else
		if(materialFilter->ShaderData->GetShaderType() == ST_LINE)
		{
			GlobalRefs::Graphics->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		}

		// Bind Textures And Materials Here

		// Render Final Mesh
		D3DX11_TECHNIQUE_DESC techDesc;
		materialFilter->ShaderData->GetEffectTechnique()->GetDesc(&techDesc);

	//	techDesc.
	//	cout<<"Passes Count : "<<techDesc.Name<<endl;
	//	cout<<"VertexCount : "<<meshFilter->MeshData->VertexCount<<" IndexCount : "<<meshFilter->MeshData->IndexCount<<endl;

		for(int p = 0; p < techDesc.Passes; p++)
		{
			materialFilter->ShaderData->GetEffectTechnique()->GetPassByIndex(p)->Apply(0, GlobalRefs::Graphics->DeviceContext);
		//	cout<<"Index Count : "<<materialFilter->IndexCount<<endl;
			
			GlobalRefs::Graphics->DeviceContext->DrawIndexed(meshFilter->MeshData->IndexCount, materialFilter->StartIndex, 0);
		}
	}
}

void RenderSystem::Destroy()
{
	cout<<"---- Destroying Render System ----"<<endl;
	TransformList = NULL;
	RenderList = NULL;
	SAFE_DELETE(Group);
	SAFE_DELETE(MeshFilterList);
	SAFE_DELETE(MaterialFilterList);
	cout<<"----------------------------------"<<endl;
}

void RenderSystem::ConstructPerspectiveMatrix(float fieldOfView, float screenWidth, float screenHeight, float screenNear, float screenFar)
{
	Projection = Matrix4x4f::Perspective(fieldOfView, screenWidth / screenHeight, screenNear, screenFar);
}

void RenderSystem::ConstructOrthographicMatrix(float screenWidth, float screenHeight, float screenNear, float screenFar)
{
	Projection = Matrix4x4f::Orthographic(0, screenWidth, 0, screenHeight, screenNear, screenFar);
}

void RenderSystem::ConstructViewMatrix()
{
	View = Matrix4x4f::LookAtLH(Vector3f(0, 0, 0), Vector3f(0, 0, 1), Vector3f(0, 1, 0));
}

void RenderSystem::FPSTestCam()
{
	float distance = Speed * GlobalRefs::Time->GetDeltaTime();
	float angle = 10.0f * GlobalRefs::Time->GetDeltaTime();
	float rollSpeed = 100 * GlobalRefs::Time->GetDeltaTime();

	// Keyboard Controller
	if(GlobalRefs::Input->KeyDown(DIK_W))
	{
		Velocity += Look * distance;
	}

	if(GlobalRefs::Input->KeyDown(DIK_S))
	{
		Velocity -= Look * distance;
	}

	if(GlobalRefs::Input->KeyDown(DIK_A))
	{
		Velocity -= Right * distance;
	}

	if(GlobalRefs::Input->KeyDown(DIK_D))
	{
		Velocity += Right * distance;
	}

	if(GlobalRefs::Input->KeyDown(DIK_R))
	{
		Velocity += Up * distance;
	}

	if(GlobalRefs::Input->KeyDown(DIK_F))
	{
		Velocity -= Up * distance;
	}

	// Camera Pitch
	if(GlobalRefs::Input->KeyDown(DIK_UP))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Right, Mathf::DegreeToRadian(-angle));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	if(GlobalRefs::Input->KeyDown(DIK_DOWN))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Right, Mathd::DegreeToRadian(angle));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	// Camera Yaw
	if(GlobalRefs::Input->KeyDown(DIK_LEFT))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Up, Mathd::DegreeToRadian(-angle));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	if(GlobalRefs::Input->KeyDown(DIK_RIGHT))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Up, Mathd::DegreeToRadian(angle));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	// Camera Roll
	if(GlobalRefs::Input->KeyDown(DIK_Q))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Look, Mathd::DegreeToRadian(rollSpeed));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	if(GlobalRefs::Input->KeyDown(DIK_E))
	{
		Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Look, Mathd::DegreeToRadian(-rollSpeed));

		Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
		Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
		Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
	}

	// Mouse Controller
	if(GlobalRefs::Input->MouseButtonDown(1))
	{
		// Yaw
		if(GlobalRefs::Input->GetMouseMovementX() != 0)
		{
			Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Up, Mathd::DegreeToRadian(GlobalRefs::Input->GetMouseMovementX() * angle));

			Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
			Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
			Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
		}

		// Pitch
		if(GlobalRefs::Input->GetMouseMovementY() != 0)
		{
			Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(Right, Mathd::DegreeToRadian(GlobalRefs::Input->GetMouseMovementY() * angle));

			Look = Matrix4x4f::Vec3TransformNormal(Look, rotMatrix);
			Up = Matrix4x4f::Vec3TransformNormal(Up, rotMatrix);
			Right = Matrix4x4f::Vec3TransformNormal(Right, rotMatrix);
		}
	}

	if(GlobalRefs::Input->KeyDown(DIK_Z))
	{
		Speed += 0.01f * GlobalRefs::Time->GetDeltaTime();
	}

	if(GlobalRefs::Input->KeyDown(DIK_X))
	{
		Speed -= 0.01f * GlobalRefs::Time->GetDeltaTime();
	}

//	Camera->SetPosition(Camera->GetPosition() + Velocity);
	CamPos = CamPos + Velocity;
//	Camera->SetAudioListenerPosition(Camera->GetPosition());

	LookAt = /*Camera->GetPosition()*/CamPos + Look;
	Look.Normalize();
	Right = Vector3f::Cross(Up, Look);
	Right.Normalize();
	Up = Vector3f::Cross(Look, Right);
	Up.Normalize();

	View = Matrix4x4f::LookAtLH(CamPos, LookAt, Up);

	Velocity = Vector3f::Lerp(Velocity, Vector3f(0, 0, 0), GlobalRefs::Time->GetDeltaTime() * 4);

//	cout<<"CX : "<<CamPos.X<<" , CY : "<<CamPos.Y<<" , CZ : "<<CamPos.Z<<endl;
}
