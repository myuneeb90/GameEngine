#include "CoreEngine/AppMain.h"

TransformSystem::TransformSystem()
{
	Group = NULL;
	TransformList = NULL;
}

TransformSystem::~TransformSystem()
{
	this->Destroy();
}

void TransformSystem::Initialize(EntityPool *pool)
{
	// use the pool to populate this entity group
	Group = new EntityGroup();
	TransformList = new EList<TransformComponent>();

	for(int i = 0; i < pool->EntityList->Count; i++)
	{
		for(int j = 0; j < pool->EntityList->GetNodeData(i)->ComponentList->Count; j++)
		{
			if(pool->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j)->Type == CIT_TRANSFORM)
			{
				Group->AddEntity(pool->EntityList->GetNodeData(i));
				TransformList->Add((TransformComponent*)pool->EntityList->GetNodeData(i)->ComponentList->GetNodeData(j));
				break;
			}
		}
	}
//	cout<<"Before Transform Crash"<<endl;
//	cout<<"Transform Count : "<<TransformList->Count<<endl;
}

void TransformSystem::Execute()
{
	for(int i = 0; i < TransformList->Count; i++)
	{
		TransformList->GetNodeData(i)->WorldMatrix = ConstructWorldMatrix(TransformList->GetNodeData(i));					
	}
}

void TransformSystem::Destroy()
{
	TransformList = NULL;
	SAFE_DELETE(Group);
//	SAFE_DELETE(TransformList);
}

Matrix4x4f TransformSystem::ConstructWorldMatrix(TransformComponent *transform)
{
	Matrix4x4f rotateXMatrix;
	Matrix4x4f rotateYMatrix;
	Matrix4x4f rotateZMatrix;
	Matrix4x4f rotationMatrix;
	Matrix4x4f scaleMatrix;
	Matrix4x4f translationMatrix;

	if(transform->RotType == RT_EULER)
	{
		rotateXMatrix = Matrix4x4f::RotateX(transform->Rotation.X);
		rotateYMatrix = Matrix4x4f::RotateY(transform->Rotation.Y);
		rotateZMatrix = Matrix4x4f::RotateZ(transform->Rotation.Z);
	}
	else
	if(transform->RotType == RT_QUATERNION)
	{
		rotationMatrix = transform->RotationQ.ToRotationMatrixf();
	}

	scaleMatrix = Matrix4x4f::Scale(transform->Scale);
	translationMatrix = Matrix4x4f::Translate(transform->Position);

	if(transform->RotType == RT_EULER)
	{
		transform->WorldMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * translationMatrix;
	}
	else
	if(transform->RotType == RT_QUATERNION)
	{
		transform->WorldMatrix = rotationMatrix * scaleMatrix * translationMatrix;
	}

	return transform->WorldMatrix;
}

//Matrix4x4f TransformSystem::ConstructWorldMatrix(TransformComponent *transform, Matrix4x4f parent)
//{
//
//}