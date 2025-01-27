/*!
@file GameStart.cpp
@brief �X�e�[�W���J�n���邽�߂̏���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameStart::GameStart(shared_ptr<Stage>& ptrStage,int mode,int enemyUpClearNum) :
		GameObject(ptrStage),
		m_stageMode(mode),
		m_EnemyUpClearNum(enemyUpClearNum)
	{

	}

	GameStart::~GameStart()
	{

	}

	//�J�n������
	void GameStart::OnCreate()
	{
		auto stage = GetStage();

		//�I�u�W�F�N�g��~����
		auto objVec = stage->GetGameObjectVec();
		//�A�N�^�[���p�����Ă�����̂����擾
		for (auto obj : objVec)
		{
			auto actorCast = dynamic_pointer_cast<Actor>(obj);
			auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

			//�A�N�^�[���p�����Ă���I�u�W�F�N�g��~
			if (actorCast)
			{
				actorCast->MoveSwitch(false);//�����Ȃ��悤�ɂ���
				m_actorVec.push_back(actorCast);
			}
			if (spriteCast)
			{
				spriteCast->OnClear(true);//�����ɂ���
			}
		}

		//����̓G��ł��グ��ƌ������ł��郂�[�h
		if (m_stageMode == 1)
		{
			m_sprite = stage->AddGameObject<Sprite>(L"ClearConditionsText1",Vec2(1280,800));
			m_spriteVec.push_back(m_sprite);
			auto sprite2 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			m_spriteVec.push_back(sprite2);
			auto sprite3 = stage->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -302.0f, 0.0f));
			sprite3->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			m_spriteVec.push_back(sprite3);
		}
		//�G����萔�ł��グ��ƌ������ł��郂�[�h
		if (m_stageMode == 2)
		{
			auto sprite = stage->AddGameObject<Sprite>(L"ClearConditionsText2", Vec2(1280, 800));
			m_spriteVec.push_back(sprite);
			auto sprite2 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			m_spriteVec.push_back(sprite2);
			auto sprite3 = stage->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -302.0f, 0.0f));
			sprite3->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			m_spriteVec.push_back(sprite3);		
			//�|���ׂ��G�̐��\��
			m_nuberManager = GetStage()->AddGameObject<NuberManager>(m_EnemyUpClearNum, Vec2(150, 150), Vec3(-490.0f, 0.0f, 0.0f), true,80.0f);//��
			//auto sprite4 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			//sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			//m_spriteVec.push_back(sprite4);

		}
	}

	//�X�V����
	void GameStart::OnUpdate()
	{
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̎擾
		auto m_controler = inputDevice.GetControlerVec()[0];
		auto Stage = GetStage();

		//B�{�^������������Q�[���X�^�[�g
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			Stage->RemoveGameObject<GameStart>(GetThis<GameStart>());
			//���������X�v���C�g���폜���鏈��
			for (auto sprite : m_spriteVec)
			{
				auto test = dynamic_pointer_cast<Sprite>(sprite);
				Stage->RemoveGameObject<Sprite>(test);
			}

			auto objVec = Stage->GetGameObjectVec();
			for (auto obj : objVec)
			{
				auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

				if (spriteCast)
				{
					spriteCast->OnClear(false);//��������߂�
				}
			}
			//�X�e�[�W���[�h�������̓G��|�����[�h�Ȃ�
			if (m_stageMode == 2)
			{
				m_nuberManager->SetDestroyFlag(true);//�i���o�[�}�l�[�W�����폜����t���O�𗧂Ă�
			}


		}
	}

	//�폜������
	void GameStart::OnDestroy()
	{
		//�����I�u�W�F�N�g��������悤�ɂ���
		for (auto actor : m_actorVec)
		{
			auto actorCheck = actor.lock();
			if (actorCheck)
			{
				actorCheck->MoveSwitch(true);//������
			}
		}

	}

}
//end basecross
