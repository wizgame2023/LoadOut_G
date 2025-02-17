/*!
@file UIManager.cpp
@brief UI�̃}�l�[�W���[
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIManager::UIManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_keyGetFlag(false),
		m_text(nullptr),
		m_sprite(nullptr),
		m_spriteNum(0)
	{

	}

	UIManager::~UIManager()
	{

	}

	//�쐬
	void UIManager::OnCreate()
	{
		auto stage = GetStage();
		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		int enemyUpCount = m_stageManager->GetUpEnemyCount();//�G��ł��グ���G�̐��擾
		int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//�G��ł��グ��ׂ��G�̐��擾
		int StageMode = m_stageManager->GetStageMode();//�X�e�[�W���[���擾

		//����̓G��|���Č�����肷�郂�[�h����
		if (StageMode == 1)
		{
			m_text = GetStage()->AddGameObject<Sprite>(L"EnemyUpText2", Vec2(180.0f, 100.0f), Vec3(-540.0f, 100.0f, 0.0f));//�G��|������(�e�L�X�g)
		}
		//�����G��|���Č�����肷�郂�[�h����
		if (StageMode == 2)
		{
			m_text = GetStage()->AddGameObject<Sprite>(L"EnemyUpText", Vec2(120.0f*1.2f, 60.0f*1.2f), Vec3(-560.0f, 100.0f, 0.0f));//�G��|������(�e�L�X�g)
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Slash", Vec2(20.0f, 20.0f), Vec3(-635.0f+176.0f, 100.0f, 0.0f));//�X���b�V��
			m_spriteNum = stage->AddGameObject<NuberManager>(enemyUpCount, Vec2(20.0f, 20.0f), Vec3(-635.0f + 160.0f, 400 - 300.0f, 0.0f), false);//�G��ł��グ�����v��
			m_spriteNumSecond = stage->AddGameObject<NuberManager>(enemyUpCountMax, Vec2(20.0f, 20.0f), Vec3(-635.0f + 190.0f, 400 - 300.0f, 0.0f), false);//�G��ł��グ��ڕW��
		}
	}

	//�X�V
	void UIManager::OnUpdate()
	{
		auto stage = GetStage();
		int StageMode = m_stageManager->GetStageMode();//�X�e�[�W���[���擾
		//����̓G��|���Č�����肷�郂�[�h����
		if (StageMode == 1 && !m_keyGetFlag)
		{

		}
		//�����G��|���Č�����肷�郂�[�h����
		if (StageMode == 2 && !m_keyGetFlag)
		{		
			int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//�G���΂��ڕW�����擾
			int enemyUpCount = m_stageManager->GetUpEnemyCount();
			m_spriteNum->SetNum(enemyUpCount);

			//�G��ڕW����΂�����G��|���������J�E���g���I��点�ă`�F�b�N�̃e�N�X�`�����o��
			if (enemyUpCount >= enemyUpCountMax)
			{
				stage->RemoveGameObject<Sprite>(m_sprite);//�X���b�V���폜
				m_spriteNum->SetDestroyFlag(true);//�폜�t���O���I���ɂ���
				m_spriteNumSecond->SetDestroyFlag(true);//�폜�t���O���I���ɂ���				
				
				GetStage()->AddGameObject<Sprite>(L"Check", Vec2(50.0f, 50.0f), Vec3(-640.0f + 172.0f, 400 - 295.0f, 0.0f));//�`�F�b�N�}�[�N����
				m_keyGetFlag = true;//������ɓ���Ă��邱�Ƃ�`����
			}
		}
	}

	void UIManager::BatteryHow()
	{
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		
	}

}
//end basecross
