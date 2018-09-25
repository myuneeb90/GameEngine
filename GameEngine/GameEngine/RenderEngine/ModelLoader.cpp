#include "CoreEngine/AppMain.h"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{

}

Mesh* ModelLoader::LoadModel(char *fileName)
{
	FbxManager *manager = NULL;
	FbxScene *scene = NULL;
	FbxIOSettings *iosetting = NULL;

	manager = FbxManager::Create();

	if(!manager)
	{
		cout<<"Unable to create fbx manager"<<endl;
		return NULL;
	}
	else
	{
		cout<<"Fbx sdk version : "<<manager->GetVersion()<<endl;
	}

	iosetting = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(iosetting);

	scene = FbxScene::Create(manager, "Fbx Scene");
	if(!scene)
	{
		cout<<"Error: Unable to create fbx scene"<<endl;
	}

	if(this->LoadScene(manager, scene, fileName) == true)
	{
		cout<<"Model Loaded Successfully"<<endl;
	}

	FbxNode *node = scene->GetRootNode();

	cout<<"Node Count : "<<node->GetChildCount()<<endl;

	cout<<"Node Name : "<<node->GetChild(0)->GetName()<<endl;

	FbxMesh *mesh = (FbxMesh*)node->GetChild(0)->GetNodeAttribute();

	FbxGeometryConverter *converter = new FbxGeometryConverter(manager);
	mesh = converter->TriangulateMesh(mesh);

	if(mesh->IsTriangleMesh() == true)
	{
		cout<<"Mesh is triangulated"<<endl;
	}
	else
	{
		cout<<"Mesh is quad based"<<endl;
	}

	cout<<"Vertex Count : "<<mesh->GetControlPointsCount()<<endl;
	cout<<"Index Count : "<<mesh->GetPolygonCount()<<endl;
	cout<<"Polygon Vertex Count : "<<mesh->GetPolygonVertexCount()<<endl;
//	mesh->GetPo

	Mesh *meshData = new Mesh();
	meshData->VertexCount = mesh->GetControlPointsCount();
	meshData->IndexCount = mesh->GetPolygonVertexCount();//mesh->GetPolygonCount() * 2 * 3;

//	mesh->GetElementV

	meshData->VertexData = new VertexFormat[meshData->VertexCount];
	
	for(int i = 0; i < meshData->VertexCount; i++)
	{
		FbxVector4 vertex = mesh->GetControlPointAt(i);

		meshData->VertexData[i].Vertex = Vector3f(vertex.mData[0], vertex.mData[1], vertex.mData[2]);
		cout<<"Vertex : "<<i<<" : "<<meshData->VertexData[i].Vertex.X<<" , "<<meshData->VertexData[i].Vertex.Y<<" , "<<meshData->VertexData[i].Vertex.Z<<endl;
	}
	
	

	unsigned long *indices = (unsigned long*)mesh->GetPolygonVertices();

	meshData->IndexData = new unsigned long[meshData->IndexCount];



	


	

//	mesh->GetPolygonVerti

//	mesh->GetPo

	for(int i = 0; i < meshData->IndexCount; i += 3)
	{		
		meshData->IndexData[i] = indices[i];
		meshData->IndexData[i + 1] = indices[i + 1];
		meshData->IndexData[i + 2] = indices[i + 2];

		//int i0 = indices[j];
		//int i1 = indices[j + 1];
		//int i2 = indices[j + 2];
		//int i3 = indices[j + 3];

		//meshData->IndexData[i] = i0;
		//meshData->IndexData[i + 1] = i1;
		//meshData->IndexData[i + 2] = i2;

		//meshData->IndexData[i + 3] = i0;
		//meshData->IndexData[i + 4] = i3;
		//meshData->IndexData[i + 5] = i2;

	//	cout<<"Index : "<<meshData->IndexData[i]<<" , "<<meshData->IndexData[i + 1]<<" , "<<meshData->IndexData[i + 2]<<endl;
	}

//	unsigned long *indices = mesh->GetPolygonVertices();

	


	if(manager)
	{
		manager->Destroy();
	}

	cout<<"Destroying fbx sdk"<<endl;

	return meshData;

/*	Assimp::Importer importer;
	const aiScene *scene;

	scene = importer.ReadFile(fileName, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	cout<<"Importing model"<<endl;

	if(scene != NULL)
	{
		cout<<"Model Scene is not null"<<endl;
	}
	else
	{
		cout<<"Scene is null return"<<endl;
		return NULL;
	}

	if(!scene->mFlags)
	{
		cout<<"Model file failed to load"<<endl;
		return NULL;
	}

	aiNode *node = scene->mRootNode;
	aiMesh *mesh = scene->mMeshes[node->mMeshes[0]];

	vector<unsigned long> indices;

	Mesh *meshData = new Mesh();
	meshData->VertexCount = mesh->mNumVertices;
	meshData->VertexData = new VertexFormat[meshData->VertexCount];

	for(int i = 0; i < mesh->mNumVertices; i++)
	{
		meshData->VertexData[i].Vertex = Vector3f(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
	}

	for(int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	meshData->IndexCount = indices.size();
	meshData->IndexData = new unsigned long[meshData->IndexCount];

	for(int i = 0; i < meshData->IndexCount; i++)
	{
		meshData->IndexData[i] = indices[i];
	}

	return meshData; */
	return NULL;
}

bool ModelLoader::LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
{
    int lFileMajor, lFileMinor, lFileRevision;
    int lSDKMajor,  lSDKMinor,  lSDKRevision;
    //int lFileFormat = -1;
    int i, lAnimStackCount;
    bool lStatus;
    char lPassword[1024];

    // Get the file version number generate by the FBX SDK.
    FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

    // Create an importer.
    FbxImporter* lImporter = FbxImporter::Create(pManager,"");

    // Initialize the importer by providing a filename.
    const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
    lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

    if( !lImportStatus )
    {
        FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
        FBXSDK_printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

        if (lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedYet ||
            lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedAnymore)
        {
            FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
            FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
        }

        return false;
    }

    FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

    if (lImporter->IsFBX())
    {
        FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

        // From this point, it is possible to access animation stack information without
        // the expense of loading the entire file.

        FBXSDK_printf("Animation Stack Information\n");

        lAnimStackCount = lImporter->GetAnimStackCount();

        FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
        FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
        FBXSDK_printf("\n");

        for(i = 0; i < lAnimStackCount; i++)
        {
            FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

            FBXSDK_printf("    Animation Stack %d\n", i);
            FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
            FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

            // Change the value of the import name if the animation stack should be imported 
            // under a different name.
            FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

            // Set the value of the import state to false if the animation stack should be not
            // be imported. 
            FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
            FBXSDK_printf("\n");
        }

        // Set the import states. By default, the import states are always set to 
        // true. The code below shows how to change these states.
		pManager->GetIOSettings()->SetBoolProp(IMP_FBX_MATERIAL,        true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_TEXTURE,         true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_LINK,            true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_SHAPE,           true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_GOBO,            true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_ANIMATION,       true);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
    }

    // Import the scene.
    lStatus = lImporter->Import(pScene);

    if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
    {
        FBXSDK_printf("Please enter password: ");

        lPassword[0] = '\0';

        FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
        scanf("%s", lPassword);
        FBXSDK_CRT_SECURE_NO_WARNING_END

        FbxString lString(lPassword);

        pManager->GetIOSettings()->SetStringProp(IMP_FBX_PASSWORD,      lString);
        pManager->GetIOSettings()->SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

        lStatus = lImporter->Import(pScene);

        if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
        {
            FBXSDK_printf("\nPassword is wrong, import aborted.\n");
        }
    }

    // Destroy the importer.
    lImporter->Destroy();

    return lStatus;
}