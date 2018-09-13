#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

class RenderSystem : public BaseSystem
{
	private:
			EntityGroup *Group;
			EList<TransformComponent> *TransformList;
			EList<RenderComponent> *RenderList;
			EList<MeshFilter> *MeshFilterList;
			EList<MaterialFilter> *MaterialFilterList;
			Matrix4x4f View;
			Matrix4x4f Projection;
			int RenderCount;
			
			Vector3f CamPos;
			Vector3f Up;
			Vector3f Look;
			Vector3f Right;
			Vector3f LookAt;
			Vector3f CamOffset;
			Vector3f Velocity;
			float Speed;
	private:
			void ConstructPerspectiveMatrix(float fieldOfView, float screenWidth, float screenHeight, float screenNear, float screenFar);
			void ConstructOrthographicMatrix(float screenWidth, float screenHeight, float screenNear, float screenFar);
			void ConstructViewMatrix();

			void FPSTestCam();

	public:
			RenderSystem();
			virtual ~RenderSystem();

			void Initialize(EntityPool *pool);
			void Execute();
			void Destroy();
};

#endif