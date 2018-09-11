#include "CoreEngine/AppMain.h"

GameScene::GameScene()
{
	Pool = NULL;
	Renderer = NULL;
}

GameScene::~GameScene()
{

}

void GameScene::Awake()
{
	Material *mat = new Material;
	mat->DiffuseColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

	Entity *testEntity = new Entity();
	testEntity->ComponentList->Add(new TransformComponent());
	testEntity->ComponentList->Add(new RenderComponent(MeshShapes::CreateCube(2.0f), mat));
		
	Entity *testEntity2 = new Entity();
	testEntity2->ComponentList->Add(new TransformComponent());
	testEntity2->ComponentList->Add(new RenderComponent(MeshShapes::CreateCube(4.0f), mat));
	
	Pool = new EntityPool();
	Pool->AddEntity(testEntity);
	Pool->AddEntity(testEntity2);

	cout<<"Pool Entity Count : "<<Pool->EntityList->Count<<endl;

	Renderer = new RenderSystem();
	Renderer->Initialize(Pool);
}

void GameScene::Start()
{

}

void GameScene::Update()
{
	Renderer->Execute();
}

void GameScene::Render()
{

}

void GameScene::Destroy()
{
	SAFE_DELETE(Pool);
	SAFE_DELETE(Renderer);
	GlobalRefs::Debug->Log("Destroying Scene");
}