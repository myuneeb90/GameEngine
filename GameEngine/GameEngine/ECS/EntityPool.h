#ifndef ENTITY_POOL_H
#define ENTITY_POOL_H

class EntityPool
{
	public:
			EList<Entity> *EntityList;
	public:
			EntityPool();
			virtual ~EntityPool();

			void AddEntity(Entity *entity);
			void RemoveEntity(Entity *entity);
};

#endif