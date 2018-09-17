#ifndef ECS_MANAGER_H
#define ECS_MANAGER_H

class IEntity
{
	public:
			int ID;
			vector<int> ComponentList;
	public:
			IEntity() 
			{
				ID = 0;
			}

			~IEntity()
			{
				ComponentList.clear();
				cout<<"Deleting Entity "<<ID<<endl;
			}

			void AddComponent(int componentId)
			{
				ComponentList.push_back(componentId);
			}
};

struct IComponent
{
	int ID;
	ComponentIDType Type;

	IComponent()
	{
		Type = CIT_BASE;
	}

	virtual ~IComponent()
	{

	}
};

struct ITransformComponent : public IComponent
{
	ITransformComponent()
	{
		Type = CIT_TRANSFORM;
	}

	~ITransformComponent()
	{
		cout<<"Deleting Component "<<ID<<endl;
	}
};

struct IRenderComponent : public IComponent
{
	IRenderComponent()
	{
		Type = CIT_RENDER;
	}

	~IRenderComponent()
	{
		cout<<"Deleting Component "<<ID<<endl;
	}
};

enum ISystemType
{
	IST_BASE = 0,
	IST_TRANSFORM = 1,
	IST_RENDER = 2
};

class ISystem
{
	public:
			ISystemType Type;
			vector<ComponentIDType> TypeList;
			vector<IEntity*> Group;
	public:
			ISystem()
			{
				Type = IST_BASE;
			}

			virtual ~ISystem()
			{
				Group.clear();
				cout<<"Deleting System "<<Type<<endl;
			}

			void Add(IEntity *entity)
			{
				Group.push_back(entity);
			}
			
			virtual void Execute() {}
};

class ITransformSystem : public ISystem
{

	public:
			ITransformSystem()
			{
				Type = IST_TRANSFORM;
				TypeList.push_back(CIT_TRANSFORM);
			}

			void Execute()
			{
			
			}
};

class IRenderSystem : public ISystem
{
	public:
			IRenderSystem()
			{
				Type = IST_RENDER;
				TypeList.push_back(CIT_TRANSFORM);
				TypeList.push_back(CIT_RENDER);
			}

			void Execute()
			{
			
			}
};

class ECSManager
{
	private:
			list<IEntity*> EntityList;
			vector<IComponent*> ComponentList;
			list<ISystem*> SystemList;
			list<IEntity*>::iterator EIter;
		//	list<IComponent*>::iterator CIter;
			list<ISystem*>::iterator SIter;
			int EntityCount;
			int ComponentCount;
			int SystemCount;
	public:
			ECSManager();
			virtual ~ECSManager();

			void AddEntity(IEntity *entity);
			void RemoveEntity(IEntity *entity);

			void AddComponent(IEntity *entity, IComponent *component);
			void RemoveComponent(IEntity *entity, IComponent *component);

			void AddSystem(ISystem *system);
			void RemoveSystem(ISystem *system);

			void Update();
};

#endif