#ifndef BASE_SYSTEM_H
#define BASE_SYSTEM_H

class BaseSystem
{
	public:
			BaseSystem();
			virtual ~BaseSystem();

			virtual void Initialize() {}
			virtual void Execute() {}
			virtual void Destroy() {}
};

#endif