#include "CoreEngine/AppMain.h"

EntityPool::EntityPool()
{
	EntityList = NULL;
	EntityList = new EList<Entity>();
}

EntityPool::~EntityPool()
{
	cout<<"------ Destroying Entity Pool ------"<<endl;
	SAFE_DELETE(EntityList);
	cout<<"------------------------------------"<<endl;
}

void EntityPool::AddEntity(Entity *entity)
{
	EntityList->Add(entity);
}

void EntityPool::RemoveEntity(Entity *entity)
{
	EntityList->Remove(entity);
}