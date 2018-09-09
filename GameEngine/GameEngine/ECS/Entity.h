#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
	public:
			EList<BaseComponent> *ComponentList;
	public:
			Entity();
			virtual ~Entity();
};

#endif 