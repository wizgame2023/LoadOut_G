/*!
@file StageCollisionManager.cpp
@brief �X�e�[�W�̃R���W�����̊Ǘ�
�S���F�O�r�T��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageCollisionManager::StageCollisionManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_CollisionSwhich(true)
	{

	}
	StageCollisionManager::~StageCollisionManager()
	{

	}

	void StageCollisionManager::OnCreate()
	{

	}

	void StageCollisionManager::OnUpdate()
	{
		CollisionActive(m_CollisionSwhich);
	}

	void StageCollisionManager::CollisionActive(bool On)
	{
		auto stage = GetStage();

		if (On == true)
		{
			AABB CollisionActiveArea = AABB(Vec3(-150.0f, -10.0f, -150.0f), Vec3(150.0f, 10.0f, 150.0f));
			stage->GetCollisionManager()->SetRootAABB(CollisionActiveArea);
		}
		if (On == false)
		{
			AABB CollisionActiveArea = AABB(Vec3(0.0f, 100.0f, 0.0f), Vec3(0.0f, 100.0f, 0.0f));
			stage->GetCollisionManager()->SetRootAABB(CollisionActiveArea);
		}

	}

	void StageCollisionManager::SetCollisionSwhich(bool On)
	{
		m_CollisionSwhich = On;
	}

}