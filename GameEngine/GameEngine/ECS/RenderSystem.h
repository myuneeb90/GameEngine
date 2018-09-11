#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

class RenderSystem : public BaseSystem
{
	private:
			EntityGroup *Group;
			EList<MeshFilter> *MeshFilterList;
			EList<MaterialFilter> *MaterialFilterList;
	public:
			RenderSystem();
			virtual ~RenderSystem();

			void Initialize(EntityPool *pool);
			void Execute();
			void Destroy();
};

#endif