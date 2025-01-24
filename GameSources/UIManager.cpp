/*!
@file UIManager.cpp
@brief UI�̃}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIManager::UIManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	UIManager::~UIManager()
	{

	}

	//�쐬
	void UIManager::OnCreate()
	{		
		//auto stage = GetStage();
		//m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		//int enemyUpCount = m_stageManager->GetUpEnemyCount();//�G��ł��グ���G�̐��擾
		//int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//�G��ł��グ��ׂ��G�̐��擾

		//GetStage()->AddGameObject<Sprite>(L"EnemyUpText", Vec2(120.0f, 60.0f), Vec3(-580.0f, 100.0f, 0.0f));//�G��|������(�e�L�X�g)
		//GetStage()->AddGameObject<Sprite>(L"Slash", Vec2(20.0f, 20.0f), Vec3(-640.0f+147.0f, 100.0f, 0.0f));//�X���b�V��
		//auto m_spriteNum = stage->AddGameObject<NuberManager>(enemyUpCount, Vec2(20.0f, 20.0f), Vec3(-640.0f + 130.0f, 400 - 300.0f, 0.0f), false);//�G��ł��グ�鍇�v��
		//auto m_spriteNum2 = stage->AddGameObject<NuberManager>(enemyUpCountMax, Vec2(20.0f, 20.0f), Vec3(-640.0f + 165.0f, 400 - 300.0f, 0.0f), false);//�G��ł��グ��ڕW��
	}

	//�X�V
	void UIManager::OnUpdate()
	{

	}

	void UIManager::BatteryHow()
	{
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		
	}

}
//end basecross
