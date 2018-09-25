#include "CoreEngine/AppMain.h"

GameScene::GameScene()
{
	Pool = NULL;
	Renderer = NULL;
	Transformer = NULL;
	Manager = NULL;
}

GameScene::~GameScene()
{
	
}

void GameScene::Awake()
{
/*	Material *mat = new Material;
	mat->DiffuseColor = Color(1.0f, 0.5f, 0.5f, 1.0f);

	Entity *testEntity = new Entity();
	testEntity->ComponentList->Add(new TransformComponent(Vector3f(0, 0, 4), Vector3f(0, 0, 0), Vector3f(1, 1, 1)));
	testEntity->ComponentList->Add(new RenderComponent(MeshShapes::CreateCube(2.0f), mat));
		
	//Entity *testEntity2 = new Entity();
	//testEntity2->ComponentList->Add(new TransformComponent());
	//testEntity2->ComponentList->Add(new RenderComponent(MeshShapes::CreateCube(2.0f), mat));
	
	Pool = new EntityPool();
	Pool->AddEntity(testEntity);
//	Pool->AddEntity(testEntity2);

//	cout<<"Pool Entity Count : "<<Pool->EntityList->Count<<endl;

	Transformer = new TransformSystem();
	Transformer->Initialize(Pool);

	Renderer = new RenderSystem();
	Renderer->Initialize(Pool);
	*/

	Material *mat1 = new Material;
	mat1->DiffuseColor = Color(1.0f, 0.0f, 0.0f, 1.0f);

	Material *mat2 = new Material;
	mat2->DiffuseColor = Color(0.0f, 1.0f, 0.0f, 1.0f);


	Manager = new ECSManager();
	
	ModelLoader *modelLoader = new ModelLoader();

	IEntity *e1 = new IEntity(); // T R
	IEntity *e2 = new IEntity(); // T R
	IEntity *e3 = new IEntity(); // T 
	IEntity *e4 = new IEntity(); // T 
	IEntity *e5 = new IEntity();

	Manager->AddEntity(e1);
	Manager->AddEntity(e2);
	Manager->AddEntity(e3);
	Manager->AddEntity(e4);
	Manager->AddEntity(e5);

	Mesh *meshData = modelLoader->LoadModel("Assets/Models/TestModel2.fbx");

	ITransformComponent *t1 = new ITransformComponent();

	Manager->AddComponent(e1, t1);
	Manager->AddComponent(e1, new IRenderComponent(meshData, mat1));

	Manager->AddComponent(e2, new ITransformComponent(Vector3f(5, 0, 0), Vector3f(0,0,0), Vector3f(1,1,1), t1));
	Manager->AddComponent(e2, new IRenderComponent(MeshShapes::CreateSphere(2.0f, 8), mat2));

	Manager->AddComponent(e3, new ITransformComponent());
	Manager->AddComponent(e4, new ITransformComponent());

	Manager->AddComponent(e5, new IFPSCameraComponent(Vector3f(0, 0, -5), 1.1f));

	Manager->AddSystem(new IFPSCameraSystem());
	Manager->AddSystem(new ITransformSystem());
	Manager->AddSystem(new IRenderSystem());
	

	//a = new EList<int>();

	//a->Add((int*)10);
	//a->Add((int*)20);

	//for(int i = 0; i < a->Count; i++)
	//{
	//	cout<<"Int List Item Value : "<<a->Get(i)<<endl;
	//}

	//SAFE_DELETE(a);
}

void GameScene::Start()
{

}

void GameScene::Update()
{
	Manager->Update();

	//Transformer->Execute();
	//

	
	//Renderer->Execute();
	
	
//	Manager->UpdateSystems();
}

//void GameScene::Render()
//{
//	
//}

void GameScene::Destroy()
{
	cout<<"-------------------"<<endl;
	SAFE_DELETE(Manager);
	cout<<"-------------------"<<endl;
	//SAFE_DELETE(Pool);
	//SAFE_DELETE(Transformer);
	//SAFE_DELETE(Renderer);
	GlobalRefs::Debug->Log("Destroying Scene");
}

void GameScene::Resize(int width, int height)
{
	GlobalRefs::Graphics->ReleaseBuffers();
	// Release Shaders & buffer objects.
	GlobalRefs::Graphics->SwapChain->ResizeBuffers(1, width, height, GlobalRefs::Graphics->SwapChainDesc.BufferDesc.Format, 0);
	GlobalRefs::Graphics->SwapChain->GetDesc(&GlobalRefs::Graphics->SwapChainDesc);
	GlobalRefs::Graphics->CreateBuffers(width, height);
	// Recreate Shaders & buffer objects.
}