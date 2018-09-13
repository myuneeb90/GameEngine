#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H



class TransformSystem : public BaseSystem
{
	private:
			EntityGroup *Group;
			EList<TransformComponent> *TransformList;
			EList<MaterialFilter> *MaterialFilterList;
	public:
			Matrix4x4f ConstructWorldMatrix(TransformComponent *transform);
		//	Matrix4x4f ConstructWorldMatrix(TransformComponent *transform, Matrix4x4f parent);

	public:
			TransformSystem();
			virtual ~TransformSystem();

			void Initialize(EntityPool *pool);
			void Execute();
			void Destroy();
};

#endif