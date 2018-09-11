#include "CoreEngine/AppMain.h"

EntityGroup::EntityGroup()
{
	EntityList = NULL;
	EntityList = new EList<Entity>();
}

EntityGroup::~EntityGroup()
{
	EntityList = NULL;
	//SAFE_DELETE(EntityList);
}

void EntityGroup::AddEntity(Entity *entity)
{
	EntityList->Add(entity);
}

void EntityGroup::RemoveEntity(Entity *entity)
{
	EntityList->Remove(entity);
}