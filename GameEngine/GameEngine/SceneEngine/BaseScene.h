#ifndef BASESCENE_H
#define BASESCENE_H

class BaseScene
{
	protected:
			  
	public:
		   BaseScene() {}
		   virtual ~BaseScene() {}

		   virtual void Awake() {}
		   virtual void Start() {}
		   virtual void Update() {}
		   virtual void Render() {}
		   virtual void Destroy() {}
};

#endif