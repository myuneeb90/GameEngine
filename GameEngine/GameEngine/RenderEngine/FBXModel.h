#ifndef FBXMODEL_H
#define FBXMODEL_H
/*
class ModelAnimation
{
	private:
			string Name;
			int KeyFrameCount;
			float FrameRate;
			float DefaultFrameRate;
	public:
			ModelAnimation(string name, int keyFrameCount, float defaultFrameRate)
			{
				Name = name;
				KeyFrameCount = keyFrameCount;
				DefaultFrameRate = defaultFrameRate;
				FrameRate = DefaultFrameRate;
			}
			~ModelAnimation();

			string GetName()
			{
				return Name;
			}

			int GetKeyFrameCount()
			{
				return KeyFrameCount;
			}

			float GetFrameRate()
			{
				return FrameRate;
			}

			void SetFrameRate(float frameRate)
			{
				FrameRate = frameRate;
			}

			float GetDefaultFrameRate()
			{
				return DefaultFrameRate;
			}

			void ResetFrameRate()
			{
				FrameRate = DefaultFrameRate;
			}
};

class ModelAnimationController
{	
	private:
			int CurrentKeyFrame;
			int NextKeyFrame;
			ModelAnimation *CurrentAnimation;
			float FrameTimer;
			float KeyFrameFactor;
	public:
			ModelAnimationController();
			~ModelAnimationController();

			void AddAnimation(ModelAnimation *animation);
			ModelAnimation* GetCurrentAnimation();

			void Play();
			void Pause()
			{
				AnimationMode = AnimationMode::Pause;
			}

			void Stop()
			{
				AnimationMode = AnimationMode::Stop;
				FrameTimer = 0.0f;
				SetCurrentKeyFrame(0);
			}

			int GetCurrentKeyFrame()
			{
				return CurrentKeyFrame;
			}

			void SetCurrentKeyFrame(int keyFrame)
			{
				CurrentKeyFrame = (keyFrame) % CurrentAnimation->GetKeyFrameCount();
				NextKeyFrame = (CurrentKeyFrame + 1) % CurrentAnimation->GetKeyFrameCount();
				KeyFrameFactor = 0.0f;
			}

			int GetNextKeyFrame()
			{
				return NextKeyFrame;
			}

			float GetKeyFrameFactor()
			{
				return KeyFrameFactor;
			}

			bool UseQuaternionKeyFrames()
			{
				return false;
			}

			void Update()
			{
				if(CurrentAnimation == NULL || AnimationMode != AnimationMode::Play)
				{
					return;
				}

				FrameTimer += GlobalRefs::Time->GetDeltaTime();

				float invFrameRate = 1.0f / CurrentAnimation->GetFrameRate();
				while(FrameTimer > invFrameRate)
				{
					CurrentKeyFrame = (CurrentKeyFrame + 1) % CurrentAnimation->GetKeyFrameCount();
					NextKeyFrame = (CurrentKeyFrame + 1) % CurrentAnimation->GetKeyFrameCount();
					FrameTimer -= invFrameRate;
				}

				KeyFrameFactor = FrameTimer / invFrameRate;
			}
};

struct ModelBlendWeights
{
	Vector4f BlendIndices;
	Vector4f BlendWeights;

	ModelBlendWeights()
	{
		BlendIndices = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
		BlendWeights = Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
	}

	void SetBlendWeight(int index, int boneIndex, float weight)
	{
		if(index == 0)
		{
			BlendIndices.X = (float)boneIndex;
			BlendWeights.X = weight;
		}
		else
		if(index == 1)
		{
			BlendIndices.Y = (float)boneIndex;
			BlendWeights.Y = weight;
		}
		else
		if(index == 2)
		{
			BlendIndices.Z = (float)boneIndex;
			BlendWeights.Z = weight;
		}
		else
		if(index == 3)
		{
			BlendIndices.W = (float)boneIndex;
			BlendWeights.W = weight;
		}
	}
};

class ModelBoneWeights
{
	private:
			float SumWeight;
			vector<pair<int, float>> BoneWeights;
	public:
			static const unsigned int MaxBonesPerVertex;
			static const unsigned int MaxBonesPerMax;
	public:
			ModelBoneWeights() : SumWeight(0.0f)
			{

			}

			~ModelBoneWeights()
			{

			}

			void AddBoneWeight(int boneIndex, float boneWeight)
			{
				if(boneWeight <= 0.0f)
				{
					return;
				}

				SumWeight += boneWeight;
				bool isAdded = false;
				vector<pair<int, float>>::iterator it;
				for(it = BoneWeights.begin(); it != BoneWeights.end(); it++)
				{
					if(boneWeight > it->second)
					{
						BoneWeights.insert(it, make_pair(boneIndex, boneWeight));
						isAdded = true;
						break;
					}
				}

				if(isAdded == false)
				{
					BoneWeights.push_back(make_pair(boneIndex, boneWeight));
				}
			}
			
			void AddBoneWeight(pair<int, float> boneWeightPair)
			{
				AddBoneWeight(boneWeightPair.first, boneWeightPair.second);
			}

			void AddBoneWeights(const ModelBoneWeights &boneWeights)
			{

			}

			void Validate();
			void Normalize();

			int GetBoneWeightCount() const
			{
				return BoneWeights.size();
			}

			pair<int, float> GetBoneWeight(int index) const
			{
				return BoneWeights[index];
			}

			ModelBlendWeights GetBlendWeights();
};



class ModelAnimationQuaternionKeyFrame
{
	private:
			Quaternion Q;
			Vector3f Translation;
	public:
			ModelAnimationQuaternionKeyFrame(Matrix4x4f &transform)
			{
				Q = Q.ToQuaternion(transform);
				Translation = Vector3f(transform.M[3][0], transform.M[3][1], transform.M[3][2]);
			}

			Quaternion& GetQuaternion()
			{
				return Q;
			}

			Vector3f& GetTranslation()
			{
				return Translation;
			}
};

class ModelAnimationKeyFrames
{
	private:
			string AnimationName;
			typedef pair<Matrix4x4f, ModelAnimationQuaternionKeyFrame> Pair;
			vector<Pair> KeyFrames;
	public:
			ModelAnimationKeyFrames(string animationName);
			~ModelAnimationKeyFrames();

			void AddKeyFrame(Matrix4x4f &transform);

			string GetAnimationName();
			Matrix4x4f& GetKeyFrameTransform(int keyFrame);
			ModelAnimationQuaternionKeyFrame& GetQuaternionKeyFrame(int keyFrame);
};

class ModelSkeletonBone
{
	private:
			string Name;
			int ParentBoneIndex;
			vector<pair<string, ModelAnimationKeyFrames*>> animationKeyFrames;
			typedef pair<string, ModelAnimationKeyFrames*> Pair;
			Matrix4x4f BindPoseTransform;
			Matrix4x4f InvBindPoseTransform;
			Matrix4x4f BoneReferenceTransform;
			Matrix4x4f InvBoneReferenceTransform;
	public:
			ModelSkeletonBone(string name, int parentBoneIndex) : Name(name), ParentBoneIndex(parentBoneIndex)
			{
				BindPoseTransform.Identity();
				InvBindPoseTransform.Identity();
				BoneReferenceTransform.Identity();
				InvBoneReferenceTransform.Identity();
			}

			~ModelSkeletonBone()
			{
				for each(Pair temp in animationKeyFrames)
				{
					SAFE_DELETE(temp.second);
				}
			}

			void AddAnimationKeyFrames(ModelAnimationKeyFrames *keyFrames)
			{
				animationKeyFrames.push_back(Pair(keyFrames->GetAnimationName(), keyFrames));
			}

			void SetBindPoseTransform(Matrix4x4f &bindPoseTransform)
			{
				this->BindPoseTransform = bindPoseTransform;
				InvBindPoseTransform = Matrix4x4f::Inverse(this->BindPoseTransform);
			}

			void SetBoneReferenceTransform(Matrix4x4f &boneReferenceTransform)
			{
				this->BoneReferenceTransform = boneReferenceTransform;
				InvBoneReferenceTransform = Matrix4x4f::Inverse(this->BoneReferenceTransform);
			}

			ModelAnimationKeyFrames* GetAnimationKeyFrames(string animationName)
			{

			}

			Matrix4x4f& GetBindPoseTransform()
			{
				return BindPoseTransform;
			}

			Matrix4x4f& GetInvBindPoseTransform()
			{
				return InvBindPoseTransform;
			}

			Matrix4x4f& GetBoneReferenceTransform()
			{
				return BoneReferenceTransform;
			}

			Matrix4x4f& GetInvBoneReferenceTransform()
			{
				return InvBoneReferenceTransform;
			}

			string GetName()
			{
				return Name;
			}
			int GetParentBoneIndex()
			{
				return ParentBoneIndex;
			}
};

class ModelSkeleton
{
	private:
			int BoneCount;
			Matrix4x4f *SkinTransforms;
			Matrix4x4f *BoneAnimationTransforms;
			typedef pair<string, ModelSkeletonBone*> Pair;
			vector<Pair> SkeletonBones;

	public:
			ModelSkeleton()
			{

			}

			~ModelSkeleton()
			{

			}

			int GetBoneCount() 
			{
				return BoneCount;
			}

			ModelSkeletonBone* FindBone(string boneName)
			{
				for each(Pair temp in SkeletonBones)
				{
					if(boneName == temp.first)
					{
						return temp.second;
					}
				}

				return NULL;
			}

			int FindBoneIndex(string boneName)
			{
				int index = 0;
				for each(Pair temp in SkeletonBones)
				{
					if(boneName == temp.first)
					{
						return index;
					}

					index++;
				}

				return -1;
			}

			void BuildBoneTransforms(ModelAnimationController *animationController, string animationName)
			{
				if(SkinTransforms == NULL)
				{
					SkinTransforms = new Matrix4x4f[BoneCount];
				}

				if(BoneAnimationTransforms == NULL)
				{
					BoneAnimationTransforms = new Matrix4x4f[BoneCount];
				}

				int keyFrame = animationController->GetCurrentKeyFrame();
				int nextKeyFrame = animationController->GetNextKeyFrame();
				float keyFrameFactor = animationController->GetKeyFrameFactor();
				bool useQuaternionKeyFrames = animationController->UseQuaternionKeyFrames();

				int index = 0;
				vector<Pair>::const_iterator it = SkeletonBones.begin();
				for(; it != SkeletonBones.end(); ++it)
				{
					ModelSkeletonBone *bone = it->second;
					Matrix4x4f invBindPose = bone->GetInvBindPoseTransform();
					Matrix4x4f animation;
					Matrix4x4f parentAnimation;

					ModelAnimationKeyFrames *animationKeyFrames = bone->GetAnimationKeyFrames(animationName);
					
					if(useQuaternionKeyFrames == true)
					{
						ModelAnimationQuaternionKeyFrame &qKeyFrame1 = animationKeyFrames->GetQuaternionKeyFrame(keyFrame);
						ModelAnimationQuaternionKeyFrame &qKeyFrame2 = animationKeyFrames->GetQuaternionKeyFrame(nextKeyFrame);
						Quaternion &q1 = qKeyFrame1.GetQuaternion();
						Quaternion &q2 = qKeyFrame2.GetQuaternion();

						Quaternion q;

						q = Quaternion::Slerp(q1, q2, keyFrameFactor);

						animation = q.ToRotationMatrixf();
						
						Vector3f t1 = qKeyFrame1.GetTranslation();
						Vector3f t2 = qKeyFrame2.GetTranslation();

						Vector3f translation = Vector3f::Lerp(t1, t2, keyFrameFactor);

						animation.M[3][0] = translation.X;
						animation.M[3][1] = translation.Y;
						animation.M[3][2] = translation.Z;
					}
					else
					{
						animation = animationKeyFrames->GetKeyFrameTransform(keyFrame);
					}

					int parentBoneIndex = bone->GetParentBoneIndex();
					if(parentBoneIndex < 0)
					{
						parentAnimation.Identity();
					}
					else
					{
						parentAnimation = BoneAnimationTransforms[parentBoneIndex];
					}

					BoneAnimationTransforms[index] = animation * parentAnimation;
					SkinTransforms[index] = invBindPose * BoneAnimationTransforms[index];
					index++;
				}
			}

			void UpdateAnimation(ModelAnimationController *animationController)
			{
				ModelAnimation *currentAnimation = animationController->GetCurrentAnimation();
				int keyFrame = animationController->GetCurrentKeyFrame();

				if(currentAnimation == NULL)
				{
					return;
				}
				
				BuildBoneTransforms(animationController, currentAnimation->GetName());
			}

			void AddSkeletonBone(ModelSkeletonBone *skeletonBone)
			{

			}

			ModelSkeletonBone* GetSkeletonBone(int index)
			{
				return SkeletonBones[index].second;
			}

			const vector<pair<string, ModelSkeletonBone*>>& GetSkeletonBones()
			{
				return SkeletonBones;
			}

			Matrix4x4f* GetSkinTransforms()
			{
				return SkinTransforms;
			}
};



class FBXModel
{
	private:
			FbxManager *manager;
			FbxScene *scene;
			FbxGeometryConverter *converter;
			FbxImporter *importer;
			ModelSkeleton *skeleton;
			ModelAnimationController *animationController;
	private:
			void LoadScene(string file);
			void ProcessScene();
			void ProcessMaterial();
			void ProcessNode(FbxNode *node, FbxNodeAttribute::EType attribute);
			void ProcessMesh(FbxNode *node);
			void ProcessAnimations();
			void ProcessAnimation(FbxNode *node, string animationName, float frameRate, float start, float stop);
			void ProcessSkeleton(FbxNode *node);

			void ProcessBoneWeights(FbxMesh *mesh, vector<ModelBoneWeights> &meshBoneWeights);
			void ProcessBoneWeights(FbxSkin *skin, vector<ModelBoneWeights> &meshBoneWeights);

			Matrix4x4f GetAbsoluteTransformFromCurrentTake(FbxNode *node, FbxTime time);
			Matrix4x4f GetLocalTransformFromCurrentTake(FbxNode *node, FbxTime time);
	public:
			FBXModel(string fileName);
			~FBXModel();

			void Update();
			void Render();
};
*/
#endif