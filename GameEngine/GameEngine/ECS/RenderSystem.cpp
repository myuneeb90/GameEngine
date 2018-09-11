#include "CoreEngine/AppMain.h"

RenderSystem::RenderSystem()
{
	Group = NULL;
	MeshFilterList = NULL;
	MaterialFilterList = NULL;
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

			}
		}
	}

	EList<RenderComponent> *renderCompList = new EList<RenderComponent>();

	for(int i = 0; i < Group->EntityList->Count; i++)
	{
		for(int j = 0; j < Group->EntityList->GetNodeData(i)->ComponentList->Count; j++)
		{
			renderCompList->Add((RenderComponent*)Group->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j));
		}
	}

	for(int i = 0; i < renderCompList->Count; i++)
	{
		MeshFilter *meshFilter = new MeshFilter();
		meshFilter->Construct(renderCompList->GetNodeData(i)->MeshData);
		MeshFilterList->Add(meshFilter);

		MaterialFilter *materialFilter = new MaterialFilter();
		//materialFilter->
		MaterialFilterList->Add(materialFilter);
	}

//	cout<<"Render System Entity Group Count : "<<Group->EntityList->Count<<endl;
}

void RenderSystem::Execute()
{

}

void RenderSystem::Destroy()
{
	SAFE_DELETE(Group);
	SAFE_DELETE(MeshFilterList);
	SAFE_DELETE(MaterialFilterList);
}