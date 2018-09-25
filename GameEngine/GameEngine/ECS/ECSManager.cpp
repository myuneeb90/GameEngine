#include "CoreEngine/AppMain.h"

ECSManager::ECSManager()
{
	EntityCount = 0;
	ComponentCount = 0;
	SystemCount = 0;
}

ECSManager::~ECSManager()
{
	for(EIter = EntityList.begin(); EIter != EntityList.end(); ++EIter)
	{
		IEntity *entity = *EIter;
		SAFE_DELETE(entity);
	}
	EntityList.clear();

	for(int i = 0; i < ComponentList.size(); ++i)
	{
		IComponent *component = ComponentList[i];
		SAFE_DELETE(component);
	}
	ComponentList.clear();

	for(SIter = SystemList.begin(); SIter != SystemList.end(); ++SIter)
	{
		ISystem *system = *SIter;
		SAFE_DELETE(system);
	}
	SystemList.clear();

	EntityCount = 0;
	ComponentCount = 0;
	SystemCount = 0;
}

void ECSManager::AddEntity(IEntity *entity)
{
	entity->ID = EntityCount;	
	EntityList.push_back(entity);
	EntityCount++;
}

void ECSManager::RemoveEntity(IEntity *entity)
{
	EntityList.remove(entity);
}

// Check for the components that can be added either once or more than once in this function
void ECSManager::AddComponent(IEntity *entity, IComponent *component)
{
	component->ID = ComponentCount;
	entity->AddComponent(component->ID);
	ComponentList.push_back(component);
	ComponentCount++;
}

void ECSManager::RemoveComponent(IEntity *entity, IComponent *component)
{
	// Incomplete functionality
	// remove component from entity also
//	ComponentList.remove(component);
}

void ECSManager::AddSystem(ISystem *system)
{
	for(EIter = EntityList.begin(); EIter != EntityList.end(); ++EIter)
	{
		IEntity *entity = *EIter;
		int count = 0;
			
		for(int i = 0; i < entity->ComponentList.size(); i++)
		{
			if(count < system->TypeList.size())
			{
				if(ComponentList[entity->ComponentList[i]]->Type == system->TypeList[count])
				{
					count++;
				}
			}
			else
			{
				break;
			}
		}

		if(count == system->TypeList.size())
		{
			system->Add(entity);
		}
	}		

	cout<<"-----------------------------"<<endl;
	cout<<"System Entity Group Count : "<<system->Group.size()<<endl;

	for(int i = 0; i < system->Group.size(); i++)
	{
		cout<<"Entity ID"<<system->Group[i]->ID<<endl;
	}
	cout<<"-----------------------------"<<endl;

	SystemList.push_back(system);
}

void ECSManager::RemoveSystem(ISystem *system)
{
	SystemList.remove(system);
}

void ECSManager::Update()
{
	for(SIter = SystemList.begin(); SIter != SystemList.end(); ++SIter)
	{
		ISystem *system = *SIter;
		system->Execute(ComponentList);
	}
}