#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

enum EntityComponentOrderID
{
	ECOI_TRANSFORM = 0,
	ECOI_RENDER = 1,
	ECOI_CAMERA = 0
};

//struct IComponent;

class IEntity
{
	public:
			int ID;
			vector<int> ComponentList;
	public:
			IEntity() 
			{
				ID = 0;
			}

			~IEntity()
			{
				ComponentList.clear();
				cout<<"Deleting Entity "<<ID<<endl;
			}

			void AddComponent(int componentId)
			{
				ComponentList.push_back(componentId);
			}
};

struct IComponent
{
	int ID;
	ComponentIDType Type;

	IComponent()
	{
		Type = CIT_BASE;
	}

	virtual ~IComponent()
	{

	}
};

struct ITransformComponent : public IComponent
{
	Vector3f Position;
	Vector3f Rotation;
	Quaternion RotationQ;
	Vector3f Scale;
	RotationType RotType;
	Matrix4x4f WorldMatrix;
	ITransformComponent *Parent;

//	float TransformValue;

	ITransformComponent()
	{
		Position = Vector3f(0, 0, 0);
		Rotation = Vector3f(0, 0, 0);
		RotationQ = Quaternion(0, 0, 0, 1);
		Scale    = Vector3f(1, 1, 1);
		Type = CIT_TRANSFORM;
		RotType = RT_EULER;
		WorldMatrix.Identity();
		Parent = NULL;
		//TransformValue = 0.0f;
	}

	ITransformComponent(Vector3f position, Vector3f rotation, Vector3f scale, ITransformComponent *parent)
	{
		Position = position;
		Rotation = rotation;
		RotationQ = Quaternion(0, 0, 0, 1);
		Scale = scale;
		Type = CIT_TRANSFORM;
		RotType = RT_EULER;
		WorldMatrix.Identity();
		Parent = parent;
	}

	~ITransformComponent()
	{
		cout<<"Deleting Component "<<ID<<endl;
	}
};

struct IRenderComponent : public IComponent
{
	Mesh *MeshData;
	Material *MaterialData;

	//float RenderValue;

	IRenderComponent()
	{
		MeshData = NULL;
		MaterialData = NULL;
		Type = CIT_RENDER;
	//	RenderValue = 0.0f;
	}

	IRenderComponent(Mesh *meshData, Material *materialData)
	{
		MeshData = meshData;
		MaterialData = materialData;
		Type = CIT_RENDER;
	}

	~IRenderComponent()
	{
		SAFE_DELETE(MeshData);
		SAFE_DELETE(MaterialData);
		cout<<"Deleting Component "<<ID<<endl;
	}
};

struct IFPSCameraComponent : public IComponent
{
	Vector3f Position;
	Vector3f Up;
	Vector3f Look;
	Vector3f Right;
	Vector3f LookAt;
	Vector3f CamOffset;
	Vector3f Velocity;
	float Speed;

	IFPSCameraComponent(Vector3f position, float speed)
	{
		Velocity = Vector3f(0.0f, 0.0f, 0.0f);
		Up = Vector3f(0, 1, 0);
		Right = Vector3f(1, 0, 0);
		Look = Vector3f(0, 0, 1);
		LookAt = Vector3f(0, 0, 1);
		Position = position;
		Speed = speed;
		Type = CIT_FPSCAMERA;
	}
};

enum ISystemType
{
	IST_BASE = 0,
	IST_TRANSFORM = 1,
	IST_RENDER = 2,
	IST_FPSCAMERA = 3
};

class ISystem
{
	public:
			ISystemType Type;
			vector<ComponentIDType> TypeList;
			vector<IEntity*> Group;
	public:
			ISystem()
			{
				Type = IST_BASE;
			}

			virtual ~ISystem()
			{
				Group.clear();
				cout<<"Deleting System "<<Type<<endl;
			}

			void Add(IEntity *entity)
			{
				Group.push_back(entity);
			}
			
			virtual void Execute(vector<IComponent*> componentList) {}
};

class ITransformSystem : public ISystem
{

	public:
			ITransformSystem()
			{
				Type = IST_TRANSFORM;
				TypeList.push_back(CIT_TRANSFORM);
			}

			virtual ~ITransformSystem()
			{

			}

			void Execute(vector<IComponent*> componentList)
			{
				for(int i = 0; i < Group.size(); i++)
				{
					ITransformComponent *transform = (ITransformComponent*)componentList[Group[i]->ComponentList[ECOI_TRANSFORM]];
					transform->WorldMatrix = ConstructWorldMatrix(transform, transform->Parent);
					transform->Rotation += Vector3f(0, 5.1f * GlobalRefs::Time->GetDeltaTime(), 0);
				}
			}

			Matrix4x4f ConstructWorldMatrix(ITransformComponent *transform)
			{
				Matrix4x4f rotateXMatrix;
				Matrix4x4f rotateYMatrix;
				Matrix4x4f rotateZMatrix;
				Matrix4x4f rotationMatrix;
				Matrix4x4f scaleMatrix;
				Matrix4x4f translationMatrix;

				if(transform->RotType == RT_EULER)
				{
					rotateXMatrix = Matrix4x4f::RotateX(transform->Rotation.X);
					rotateYMatrix = Matrix4x4f::RotateY(transform->Rotation.Y);
					rotateZMatrix = Matrix4x4f::RotateZ(transform->Rotation.Z);
				}
				else
				if(transform->RotType == RT_QUATERNION)
				{
					rotationMatrix = transform->RotationQ.ToRotationMatrixf();
				}

				scaleMatrix = Matrix4x4f::Scale(transform->Scale);
				translationMatrix = Matrix4x4f::Translate(transform->Position);

				if(transform->RotType == RT_EULER)
				{
					transform->WorldMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * translationMatrix;
				}
				else
				if(transform->RotType == RT_QUATERNION)
				{
					transform->WorldMatrix = rotationMatrix * scaleMatrix * translationMatrix;
				}

				return transform->WorldMatrix;
			}

			Matrix4x4f ConstructWorldMatrix(ITransformComponent *transform, ITransformComponent *parent)
			{
				Matrix4x4f rotateXMatrix;
				Matrix4x4f rotateYMatrix;
				Matrix4x4f rotateZMatrix;
				Matrix4x4f rotationMatrix;
				Matrix4x4f scaleMatrix;
				Matrix4x4f translationMatrix;

				if(transform->RotType == RT_EULER)
				{
					rotateXMatrix = Matrix4x4f::RotateX(transform->Rotation.X);
					rotateYMatrix = Matrix4x4f::RotateY(transform->Rotation.Y);
					rotateZMatrix = Matrix4x4f::RotateZ(transform->Rotation.Z);
				}
				else
				if(transform->RotType == RT_QUATERNION)
				{
					rotationMatrix = transform->RotationQ.ToRotationMatrixf();
				}

				scaleMatrix = Matrix4x4f::Scale(transform->Scale);
				translationMatrix = Matrix4x4f::Translate(transform->Position);

				if(transform->RotType == RT_EULER)
				{
					transform->WorldMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * translationMatrix;
				}
				else
				if(transform->RotType == RT_QUATERNION)
				{
					transform->WorldMatrix = rotationMatrix * scaleMatrix * translationMatrix;
				}

				if(parent != NULL)
				{
					transform->WorldMatrix = transform->WorldMatrix * parent->WorldMatrix;
				}

				return transform->WorldMatrix;
			}
};

class IRenderSystem : public ISystem
{
	private:
			vector<MeshFilter*> MeshFilterList;
			vector<MaterialFilter*> MaterialFilterList;
			bool PrepareFilters;
	public:
			IRenderSystem()
			{
				Type = IST_RENDER;
				TypeList.push_back(CIT_TRANSFORM);
				TypeList.push_back(CIT_RENDER);
				PrepareFilters = false;
			}

			~IRenderSystem()
			{
				for(int i = 0; i < MeshFilterList.size(); ++i)
				{
					MeshFilter *meshFilter = MeshFilterList[i];
					SAFE_DELETE(meshFilter);
				}
				MeshFilterList.clear();

				for(int i = 0; i < MaterialFilterList.size(); ++i)
				{
					MaterialFilter *materialFilter = MaterialFilterList[i];
					SAFE_DELETE(materialFilter);
				}
				MaterialFilterList.clear();
			}

			void Execute(vector<IComponent*> componentList)
			{
				if(PrepareFilters == false)
				{
					for(int i = 0; i < Group.size(); i++)
					{
						IRenderComponent *render = (IRenderComponent*)componentList[Group[i]->ComponentList[ECOI_RENDER]];

						MeshFilter *meshFilter = new MeshFilter();
						meshFilter->Construct(render->MeshData);
						MeshFilterList.push_back(meshFilter);

						MaterialFilter *materialFilter = new MaterialFilter(ShadersLib::CreateDefaultShader(render->MaterialData->DiffuseColor));
						MaterialFilterList.push_back(materialFilter);
					}

					PrepareFilters = true;
				}

				GlobalRefs::Graphics->BeginRender(0.5f, 0.5f, 0.5f, 1.0f);

				for(int i = 0; i < Group.size(); i++)
				{
					ITransformComponent *transform = (ITransformComponent*)componentList[Group[i]->ComponentList[ECOI_TRANSFORM]];
					IRenderComponent *render = (IRenderComponent*)componentList[Group[i]->ComponentList[ECOI_RENDER]];

					MeshFilter *meshFilter = MeshFilterList[i];
					MaterialFilter *materialFilter = MaterialFilterList[i];

					Matrix4x4f world = transform->WorldMatrix;
					Matrix4x4f wvp;

					wvp = world * GlobalRefs::Graphics->ViewMatrix * GlobalRefs::Graphics->ProjectionMatrix;

					materialFilter->ShaderData->SetMatrix("WVP", wvp);
					materialFilter->ShaderData->SetMatrix("World", world);
		
					GlobalRefs::Graphics->DeviceContext->IASetVertexBuffers(0, 1, &meshFilter->VertexBuffer, &meshFilter->Stride, &meshFilter->Offset);
					GlobalRefs::Graphics->DeviceContext->IASetIndexBuffer(meshFilter->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
		
					GlobalRefs::Graphics->DeviceContext->IASetInputLayout(materialFilter->ShaderData->GetInputLayout());

					if(materialFilter->ShaderData->GetShaderType() == ST_MESH)
					{
						GlobalRefs::Graphics->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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

					for(int p = 0; p < techDesc.Passes; p++)
					{
						materialFilter->ShaderData->GetEffectTechnique()->GetPassByIndex(p)->Apply(0, GlobalRefs::Graphics->DeviceContext);			
						GlobalRefs::Graphics->DeviceContext->DrawIndexed(meshFilter->MeshData->IndexCount, materialFilter->StartIndex, 0);
					}
				}	

				GlobalRefs::Graphics->EndRender();
			}
};

class IFPSCameraSystem : public ISystem
{			
	public:
			IFPSCameraSystem()
			{
				Type = IST_FPSCAMERA;
				TypeList.push_back(CIT_FPSCAMERA);
				this->ConstructPerspectiveMatrix(60.0f, (float)GlobalRefs::Window->ScreenWidth, (float)GlobalRefs::Window->ScreenHeight, 0.1f, 1000);
				this->ConstructViewMatrix();
			}

			~IFPSCameraSystem()
			{

			}

			void ConstructPerspectiveMatrix(float fieldOfView, float screenWidth, float screenHeight, float screenNear, float screenFar)
			{
				GlobalRefs::Graphics->ProjectionMatrix = Matrix4x4f::Perspective(fieldOfView, screenWidth / screenHeight, screenNear, screenFar);
			}

			void ConstructOrthographicMatrix(float screenWidth, float screenHeight, float screenNear, float screenFar)
			{
				GlobalRefs::Graphics->ProjectionMatrix = Matrix4x4f::Orthographic(0, screenWidth, 0, screenHeight, screenNear, screenFar);
			}
			
			void ConstructViewMatrix()
			{
				GlobalRefs::Graphics->ViewMatrix = Matrix4x4f::LookAtLH(Vector3f(0, 0, -5), Vector3f(0, 0, 1), Vector3f(0, 1, 0));
			}

			void Execute(vector<IComponent*> componentList)
			{
				//Group
				for(int i = 0; i < Group.size(); i++)
				{
					IFPSCameraComponent *camera = (IFPSCameraComponent*)componentList[Group[i]->ComponentList[ECOI_CAMERA]];

					float distance = camera->Speed * GlobalRefs::Time->GetDeltaTime();
					float angle = 10.0f * GlobalRefs::Time->GetDeltaTime();
					float rollSpeed = 100 * GlobalRefs::Time->GetDeltaTime();

					// Keyboard Controller
					if(GlobalRefs::Input->KeyDown(DIK_W))
					{
						camera->Velocity += camera->Look * distance;
					}

					if(GlobalRefs::Input->KeyDown(DIK_S))
					{
						camera->Velocity -= camera->Look * distance;
					}

					if(GlobalRefs::Input->KeyDown(DIK_A))
					{
						camera->Velocity -= camera->Right * distance;
					}

					if(GlobalRefs::Input->KeyDown(DIK_D))
					{
						camera->Velocity += camera->Right * distance;
					}

					if(GlobalRefs::Input->KeyDown(DIK_R))
					{
						camera->Velocity += camera->Up * distance;
					}

					if(GlobalRefs::Input->KeyDown(DIK_F))
					{
						camera->Velocity -= camera->Up * distance;
					}

					// Camera Pitch
					if(GlobalRefs::Input->KeyDown(DIK_UP))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Right, Mathf::DegreeToRadian(-angle));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					if(GlobalRefs::Input->KeyDown(DIK_DOWN))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Right, Mathd::DegreeToRadian(angle));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					// Camera Yaw
					if(GlobalRefs::Input->KeyDown(DIK_LEFT))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Up, Mathd::DegreeToRadian(-angle));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					if(GlobalRefs::Input->KeyDown(DIK_RIGHT))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Up, Mathd::DegreeToRadian(angle));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					// Camera Roll
					if(GlobalRefs::Input->KeyDown(DIK_Q))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Look, Mathd::DegreeToRadian(rollSpeed));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					if(GlobalRefs::Input->KeyDown(DIK_E))
					{
						Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Look, Mathd::DegreeToRadian(-rollSpeed));

						camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
						camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
						camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
					}

					// Mouse Controller
				//	if(GlobalRefs::Input->MouseButtonDown(1))
					{
						// Yaw
						if(GlobalRefs::Input->GetMouseMovementX() != 0)
						{
							Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Up, Mathd::DegreeToRadian(GlobalRefs::Input->GetMouseMovementX() * angle));

							camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
							camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
							camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
						}

						// Pitch
						if(GlobalRefs::Input->GetMouseMovementY() != 0)
						{
							Matrix4x4f rotMatrix = Matrix4x4f::RotationAxis(camera->Right, Mathd::DegreeToRadian(GlobalRefs::Input->GetMouseMovementY() * angle));

							camera->Look = Matrix4x4f::Vec3TransformNormal(camera->Look, rotMatrix);
							camera->Up = Matrix4x4f::Vec3TransformNormal(camera->Up, rotMatrix);
							camera->Right = Matrix4x4f::Vec3TransformNormal(camera->Right, rotMatrix);
						}
					}

					if(GlobalRefs::Input->KeyDown(DIK_Z))
					{
						camera->Speed += 0.01f * GlobalRefs::Time->GetDeltaTime();
					}

					if(GlobalRefs::Input->KeyDown(DIK_X))
					{
						camera->Speed -= 0.01f * GlobalRefs::Time->GetDeltaTime();
					}

				//	Camera->SetPosition(Camera->GetPosition() + Velocity);
					camera->Position = camera->Position + camera->Velocity;
				//	Camera->SetAudioListenerPosition(Camera->GetPosition());

					camera->LookAt = /*Camera->GetPosition()*/camera->Position + camera->Look;
					camera->Look.Normalize();
					camera->Right = Vector3f::Cross(camera->Up, camera->Look);
					camera->Right.Normalize();
					camera->Up = Vector3f::Cross(camera->Look, camera->Right);
					camera->Up.Normalize();

					GlobalRefs::Graphics->ViewMatrix = Matrix4x4f::LookAtLH(camera->Position, camera->LookAt, camera->Up);

					camera->Velocity = Vector3f::Lerp(camera->Velocity, Vector3f(0, 0, 0), GlobalRefs::Time->GetDeltaTime() * 4);
				}
			}
};

class ECSManager
{
	private:
			list<IEntity*> EntityList;
			vector<IComponent*> ComponentList;
			list<ISystem*> SystemList;
			list<IEntity*>::iterator EIter;
		//	list<IComponent*>::iterator CIter;
			list<ISystem*>::iterator SIter;
			int EntityCount;
			int ComponentCount;
			int SystemCount;
	public:
			ECSManager();
			virtual ~ECSManager();

			void AddEntity(IEntity *entity);
			void RemoveEntity(IEntity *entity);

			void AddComponent(IEntity *entity, IComponent *component);
			void RemoveComponent(IEntity *entity, IComponent *component);

			void AddSystem(ISystem *system);
			void RemoveSystem(ISystem *system);

			void Update();
};

#endif