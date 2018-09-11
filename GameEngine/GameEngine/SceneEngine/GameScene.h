#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class GameScene : public BaseScene
{
	private:
			EntityPool *Pool;
			RenderSystem *Renderer;

	public:
			GameScene();
			virtual ~GameScene();

		    void Awake(); 
		    void Start(); 
		    void Update(); 
			void Render();
		    void Destroy(); 
};

#endif