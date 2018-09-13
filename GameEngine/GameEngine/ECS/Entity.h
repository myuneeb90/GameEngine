#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
	public:
			int ID;
			int ComponentID;
			EList<BaseComponent> *ComponentList;
	public:
			Entity();
			virtual ~Entity();

			void AddComponent(BaseComponent *component);
			void RemoveComponent(BaseComponent *component);
};

#endif 