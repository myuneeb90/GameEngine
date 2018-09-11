#ifndef ENTITY_GROUP_H
#define ENTITY_GROUP_H

class EntityGroup
{
	public:
			EList<Entity> *EntityList;
	public:
			EntityGroup();
			virtual ~EntityGroup();

			void AddEntity(Entity *entity);
			void RemoveEntity(Entity *entity);
};

#endif