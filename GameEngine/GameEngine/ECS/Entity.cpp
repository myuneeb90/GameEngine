#include "CoreEngine/AppMain.h"

Entity::Entity()
{
	ComponentList = NULL;
	ComponentList = new EList<BaseComponent>();
	ComponentID = 0;
}

Entity::~Entity()
{
	cout<<"------ Destroying Entity Components ------"<<endl;
	SAFE_DELETE(ComponentList);
	cout<<"------------------------------------------"<<endl;
}

void Entity::AddComponent(BaseComponent *component)
{
	component->ID = ComponentID;
	ComponentList->Add(component);
	ComponentID++;
}

void Entity::RemoveComponent(BaseComponent *component)
{
	ComponentList->Remove(component);
}