#include "CoreEngine/AppMain.h"
/*
FBXModel::FBXModel(string fileName)
{
	manager = FbxManager::Create();
	if(manager == NULL)
	{
		cout<<"Model Failed to Load"<<endl;
	}

	scene = FbxScene::Create(manager, "");
	if(scene == NULL)
	{
		cout<<"Scene Failed to Load"<<endl;
	}

	converter = new FbxGeometryConverter(manager);

	if(converter != NULL)
	{
		this->LoadScene(fileName);
	}

	SAFE_DELETE(converter);
}

FBXModel::~FBXModel()
{

}

void FBXModel::Update()
{
	bool isAnimated = false;
	if(animationController != NULL)
	{
		isAnimated = animationController->GetAnimationCount() > 0;

		if(isAnimated == true)
		{
			animationController->Update();

			if(skeleton != NULL)
			{
				skeleton->UpdateAnimation(animationController);
			}

			for each(Model *model in models)
			{
				model->UpdateAnimation(animationController);
			}
		}
	}

	if(skeleton != NULL)
	{
		Matrix4x4f *bonesArray = skeleton->GetSkinTransforms();
		if(bonesArray != NULL)
		{
			unsigned int boneCount = skeleton->GetBoneCount();
			boneCount = boneCount < ModelBoneWeights::MaxBonesPerMax ? boneCount : ModelBoneWeights::MaxBonesPerMax;
			modelBuffer->SetBoneArray(bonesArray, boneCount);
		}
	}

	modelBuffer->SetSkinning(isAnimated);
	modelBuffer->Update();

	for each(Model *model in models)
	{
		model->Update(isAnimated);
	}
}

void FBXModel::Render()
{
	modelBuffer->SetVSBuffer(2);
	for each(Model *model in models)
	{
		model->Render();
	}
}

void FBXModel::LoadScene(string file)
{

}

void FBXModel::ProcessScene()
{
	skeleton = NULL;
	animationController = NULL;

	ProcessNode(scene->GetRootNode(), FbxNodeAttribute::eSkeleton);
	ProcessNode(scene->GetRootNode(), FbxNodeAttribute::eMesh);
	ProcessAnimations();
}

void FBXModel::ProcessMaterial()
{

}

void FBXModel::ProcessNode(FbxNode *node, FbxNodeAttribute::EType attribute)
{
	FbxNodeAttribute *nodeAttribute = node->GetNodeAttribute();
	if(nodeAttribute != NULL)
	{
		if(nodeAttribute->GetAttributeType() == attribute)
		{
			if(nodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			{
				ProcessSkeleton(node);
			}
			else
			if(nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
			{
				ProcessMesh(node);
			}
		}
	}
}

void FBXModel::ProcessMesh(FbxNode *node)
{

}

void FBXModel::ProcessAnimations()
{
	animationController = new ModelAnimationController();

	FbxNode *rootNode = scene->GetRootNode();
	if(rootNode == NULL)
	{
		return;
	}

	float frameRate = (float)FbxTime::GetFrameRate(scene->GetGlobalSettings().GetTimeMode());

	FbxArray<FbxString*> animationArray;
	FbxDocument *document = dynamic_cast<FbxDocument*>(scene);
	if(document != NULL)
	{
		document->FillAnimStackNameArray(animationArray);
	}

	for(int i = 0; i < importer->GetAnimStackCount(); i++)
	{
		FbxTakeInfo *animationInfo = importer->GetTakeInfo(i);
		string animationName = animationInfo->mName.Buffer();

		FbxTimeSpan span = animationInfo->mLocalTimeSpan;

		double startTime = span.GetStart().GetSecondDouble();
		double endTime = span.GetStop().GetSecondDouble();

		if(startTime < endTime)
		{
			int keyFrames = (int)((endTime - startTime) * (double)frameRate);
			ModelAnimation *animation = new ModelAnimation(animationName, keyFrames, frameRate);
			animationController->AddAnimation(animation);

			ProcessAnimation(rootNode, animationName, frameRate, (float)startTime, (float)endTime);

			animationController->SetCurrentAnimation(0);
			animationController->Play();
		}
	}

	animationArray.Clear();
}

void FBXModel::ProcessAnimation(FbxNode *node, string animationName, float frameRate, float start, float stop)
{
	FbxNodeAttribute *nodeAttribute = node->GetNodeAttribute();
	if(nodeAttribute != NULL)
	{
		if(nodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			if(skeleton != NULL)
			{
				string boneName = node->GetName();
				ModelSkeletonBone *bone = skeleton->FindBone(boneName);

				if(bone != NULL)
				{
					ModelAnimationKeyFrames *animationKeyFrames = new ModelAnimationKeyFrames(animationName);
					double time = 0;

					while(time <= (double)stop)
					{
						FbxTime animationTime;
						animationTime.SetSecondDouble(time);

						Matrix4x4f localTransform = GetLocalTransformCurrentTake(node, animationTime);
						animationKeyFrames->AddKeyFrame(localTransform);

						time += 1.0f;
					}
					bone->AddAnimationKeyFrames(animationKeyFrames);
				}
			}
		}
		else
		if(nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			Model *model = NULL;
			for each(Model *tempModel in models)
			{
				string modelName = node->GetName();
				if(modelName == tempModel->GetName())
				{
					model = tempModel;
					break;
				}
			}

			if(model != NULL)
			{
				ModelAnimationKeyFrames *animationKeyFrames = new ModelAnimationKeyFrames(animationName);
				double time = 0;
				while(time <= (double)stop)
				{
					FbxTime animationTime;
					animationTime.SetSecondDouble(time);

					Matrix4x4f absoluteTransform = GetAbsoluteTransformFromCurrentTake(node, animationTime);
					animationKeyFrames->AddKeyFrame(absoluteTransform);

					time += 1.0f / frameRate;
				}

				model->AddAnimationKeyFrames(animationKeyFrames);
			}
		}
	}

	for(int i = 0; i < node->GetChildCount(); ++i)
	{
		ProcessAnimation(node->GetChild(i), animationName, frameRate, start, stop);
	}
}

void FBXModel::ProcessSkeleton(FbxNode *node)
{
	FbxSkeleton *fbxSkeleton = node->GetSkeleton();
	if(fbxSkeleton == NULL)
	{
		return;
	}

	if(skeleton == NULL)
	{
		skeleton = new ModelSkeleton();
	}

	int parentBoneIndex = -1;
	FbxNode *parentNode = node->GetParent();
	if(parentNode != NULL)
	{
		string boneName = parentNode->GetName();
		parentBoneIndex = skeleton->FindBoneIndex(boneName);
	}

	string boneName = node->GetName();
	ModelSkeletonBone *skeletonBone = new ModelSkeletonBone(boneName, parentBoneIndex);
	skeleton->AddSkeletonBone(skeletonBone);
}

void FBXModel::ProcessBoneWeights(FbxMesh *mesh, vector<ModelBoneWeights> &meshBoneWeights)
{

}

void FBXModel::ProcessBoneWeights(FbxSkin *skin, vector<ModelBoneWeights> &meshBoneWeights)
{

}

Matrix4x4f FBXModel::GetAbsoluteTransformFromCurrentTake(FbxNode *node, FbxTime time)
{
	if(node == NULL)
	{
		Matrix4x4f mat;
		mat.Identity();
		return mat;
	}

	FbxAMatrix matrix = node->EvaluateGlobalTransform(time);
	
	return; // Convert matrix to Matrix4x4f Later
}

Matrix4x4f FBXModel::GetLocalTransformFromCurrentTake(FbxNode *node, FbxTime time)
{
	if(node == NULL)
	{
		Matrix4x4f mat;
		mat.Identity();
		return mat;
	}

	FbxAMatrix matrix = node->EvaluateLocalTransform(time);

	return; // Convert matrix to Matrix4x4f Later
}
*/