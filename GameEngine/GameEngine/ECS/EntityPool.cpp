#include "CoreEngine/AppMain.h"

EntityPool::EntityPool()
{
	EntityList = NULL;
	EntityList = new EList<Entity>();
	Count = 0;
}

EntityPool::~EntityPool()
{
	cout<<"------ Destroying Entity Pool ------"<<endl;
	SAFE_DELETE(EntityList);
	cout<<"------------------------------------"<<endl;
}

void EntityPool::AddEntity(Entity *entity)
{
	entity->ID = Count;
	EntityList->Add(entity);
	Count++;
}

void EntityPool::RemoveEntity(Entity *entity)
{
	EntityList->Remove(entity);
}