#include "CoreEngine/AppMain.h"

Entity::Entity()
{
	ComponentList = NULL;
	ComponentList = new EList<BaseComponent>();
}

Entity::~Entity()
{
	cout<<"------ Destroying Entity Components ------"<<endl;
	SAFE_DELETE(ComponentList);
	cout<<"------------------------------------------"<<endl;
}

void Entity::AddComponent(BaseComponent *component)
{
	ComponentList->Add(component);
}

void Entity::RemoveComponent(BaseComponent *component)
{
	ComponentList->Remove(component);
}