#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class GameScene : public BaseScene
{
	private:
			EntityPool *Pool;
			TransformSystem *Transformer;
			RenderSystem *Renderer;
			ECSManager *Manager;
		//	EList<int> *a;
	public:
			GameScene();
			virtual ~GameScene();

		    void Awake(); 
		    void Start(); 
		    void Update(); 
		//	void Render();
		    void Destroy(); 
			void Resize(int width, int height);
};

#endif