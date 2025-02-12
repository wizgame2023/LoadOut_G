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
		m_EnemyUpClearNum(enemyUpClearNum),
		m_step(GAMESTART_Start)
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

		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		stageManager->SetUpdateFlag(false);//�X�V�ł��Ȃ��悤�ɂ���

		//auto m_StageText = stage->AddGameObject<Sprite>(L"StageText", Vec2(800/2, 150/2), Vec3(-105.0f, 250.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
		//m_StageText->SetDrawLayer(2);
		auto m_NumberSprite = stage->AddGameObject<NuberManager>(1, Vec2(150/2, 150/2), Vec3(-55.0f, 150.0f, 0.0f), true, 35.0f,2);//���݂̃X�e�[�W���o��

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
		auto stage = GetStage();
		bool removeFlag = false;
		auto delta = App::GetApp()->GetElapsedTime();

		//B�{�^������������J�E���g�_�E��������
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B && m_step == GAMESTART_Start)
		{
			//���������X�v���C�g���폜���鏈��
			for (auto sprite : m_spriteVec)
			{
				auto castSprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castSprite)
				{
					stage->RemoveGameObject<Sprite>(castSprite);
				}
			}
			//�X�e�[�W���[�h�������̓G��|�����[�h�Ȃ�
			if (m_stageMode == 2)
			{
				m_nuberManager->SetDestroyFlag(true);//�i���o�[�}�l�[�W�����폜����t���O�𗧂Ă�
			}

			m_spriteVec.clear();//�X�v���C�g�z��̃��Z�b�g

			m_step = GAMESTART_CountDown_One;//�X�e�b�v�X�V

			//�J�E���g�_�E��SE�Đ�
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			SEManager->Start(L"CountDownSE", 0, 3.5f);

		}

		//�J�E���g�_�E��
		if (m_step == GAMESTART_CountDown_One)
		{			
			m_CountDownTimeCount += delta;
			//�o�Ă��鎞�Ԃɏ������O��t����3���o��
			if (m_CountDownTimeCount > 0.1f)
			{
				m_spriteCountDown = stage->AddGameObject<Sprite>(L"3Tex", Vec2(500, 500));
				m_spriteVec.push_back(m_spriteCountDown);
				m_step = GAMESTART_CountDown_Two;//�X�e�b�v�X�V
			}
		}

		if (m_step == GAMESTART_CountDown_Two)
		{
			m_CountDownTimeCount += delta;
			//2���o��
			if (m_CountDownTimeCount > 1.0f)
			{
				m_spriteCountDown->SetTexture(L"2Tex");
				m_step = GAMESTART_CountDown_Three;//�X�e�b�v�X�V
			}
		}

		if (m_step == GAMESTART_CountDown_Three)
		{
			m_CountDownTimeCount += delta;
			//1���o��
			if (m_CountDownTimeCount > 2.0f)
			{
				m_spriteCountDown->SetTexture(L"1Tex");
				m_step = GAMESTART_CountDown_Start;//�X�e�b�v�X�V

			}
		}

		if (m_step == GAMESTART_CountDown_Start)
		{
			m_CountDownTimeCount += delta;
			//Start���o��
			if (m_CountDownTimeCount > 3.0f)
			{
				m_spriteCountDown->SetTexture(L"Clear");//�����X�v���C�g�ɒu������
				m_spriteCountDown = stage->AddGameObject<Sprite>(L"StartTex", Vec2(1000, 1000));
				m_spriteVec.push_back(m_spriteCountDown);

				m_step = GAMESTART_End;//�X�e�b�v�X�V
			}
		}

		if (m_step == GAMESTART_End)
		{
			m_CountDownTimeCount += delta;
			//������xStart�̃e�N�X�`������������
			if (m_CountDownTimeCount > 3.5f)
			{
				removeFlag = true;//�폜���J�n����
			}
		}

		//�J�E���g�_�E�����I��������������������
		if (removeFlag)
		{
			stage->RemoveGameObject<GameStart>(GetThis<GameStart>());
			//���������X�v���C�g���폜���鏈��
			for (auto sprite : m_spriteVec)
			{
				auto castSprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castSprite)
				{
					stage->RemoveGameObject<Sprite>(castSprite);
				}
			}

			auto objVec = stage->GetGameObjectVec();
			for (auto obj : objVec)
			{
				auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

				if (spriteCast)
				{
					spriteCast->OnClear(false);//��������߂�
				}
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
		auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
		stageManager->SetUpdateFlag(true);//�X�V�ł���悤�ɂ���


	}

}
//end basecross
