#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

class ModelLoader
{
	private:

	public:
			ModelLoader();
			~ModelLoader();

			Mesh* LoadModel(char *fileName);
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);
};

#endif