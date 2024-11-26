/*!
@file StageManaegr.cpp
@brief �X�e�[�W�̐i�s���Ǘ�����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	StageManager::~StageManager()
	{

	}

	void StageManager::OnCreate()
	{
		auto stage = GetStage();

		//BGM�Đ�
		m_BGMChase = 2;
		m_bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);
		auto a = 0;
	}

	void StageManager::OnUpdate()
	{
		BGMChange();

		//�ǂ��������Ă���Ȃ�ǂ��������Ă���BGM
		if (m_BGMChase&&m_BGMhow !=1)
		{
			m_BGMhow = 1;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"TIlteStage", XAUDIO2_LOOP_INFINITE, 0.9f);
			auto test = 0;
		}
		//�ǂ��������Ă��Ȃ���Ε��ʂ�BGM
		if (!m_BGMChase&&m_BGMhow !=2)
		{
			m_BGMhow = 2;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		}
	}

	void StageManager::BGMChange()
	{
		auto stage = GetStage();
		auto obj = stage->GetGameObjectVec();
		auto EnemyTracking = 0;
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto enemy : obj)
		{
			auto enemycast = dynamic_pointer_cast<Enemy>(enemy);

			if (enemycast)//Enemy�^�ɃL���X�g�ɐ���������
			{
				auto State = enemycast->GetNowState();//���݂̃X�e�[�g���󂯎��
				auto trackcast = dynamic_pointer_cast<Tracking>(State);
				if (trackcast)//���݂̃X�e�[�g���g���b�L���O(�ǂ������鏈��)�̎�
				{
					EnemyTracking++;
				}
			}
		}
		m_BGMChase;//�ǂ�������G�����邩
		if (EnemyTracking > 0)//�ǂ�������G����l�ȏア��Ȃ�
		{
			m_BGMChase = true;
		}
		else
		{
			m_BGMChase = false;
		}

		
	}

	void StageManager::OnDestroy()
	{

	}


}
//end basecross
