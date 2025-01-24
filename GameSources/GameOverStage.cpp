/*!
@file GameOverStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(2.0f, 20.0f, -10.0f));
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameOverStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Sprite>(L"GameOverLight", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
			AddGameObject<Sprite>(L"GameOverText", Vec2(800, 300), Vec3(0.0f, 300.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
			m_clearText1 = AddGameObject<Sprite>(L"GameClearText3", Vec2(300, 150), Vec3(-400.0f, -350.0f, 0.0f));//�N���A�p�̃X�v���C�g����
			m_clearText2 = AddGameObject<Sprite>(L"GameClearText2", Vec2(400, 130), Vec3(0.0f, -350.0f, 0.0f));//�N���A�p�̃X�v���C�g����
			m_clearText3 = AddGameObject<Sprite>(L"GameClearText1", Vec2(300, 150), Vec3(400.0f, -350.0f, 0.0f));//�N���A�p�̃X�v���C�g����

		}
		catch (...) {
			throw;
		}

		//auto BGM = App::GetApp()->GetXAudio2Manager();
		//auto bgm = BGM->Start(L"GameOver", 0, 0.9f);

		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"GameOverBGM", 0, 0.9f);

		//�}�b�v�}�l�[�W���[�̐���
		auto mapManager = AddGameObject<MapManager>(L"GameOverStage/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();


		auto player = AddGameObject<Player>(Vec3(5.0f, 0.0f, 25.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), false);
		SetSharedGameObject(L"Player", player);
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Player_Down");//�|��郂�[�V�����ɕύX
		//Player�̃A�j���[�V�����X�V
		playerDraw->UpdateAnimation(99.0f);



		//���̍쐬
		AddGameObject<Ground>();

		//�Ō�Ƀv���C�����X�e�[�W��n��
		auto m_lastStage = App::GetApp()->GetScene<Scene>()->GetLastPlayStage();


	}



	void GameOverStage::OnUpdate()
	{
		//auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��

		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//�L�[�{�[�h�f�o�b�N�p
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto m_controler = inputDevice.GetControlerVec()[0];

		auto m_lastPlayStage = App::GetApp()->GetScene<Scene>()->GetLastPlayStage();

		if (m_controler.fThumbLX > 0 && !m_stickCheck && m_count < 2)
		{
			m_count++;
			m_stickCheck = true;

		}
		if (m_controler.fThumbLX < 0 && !m_stickCheck && m_count > 0)
		{
			m_count--;
			m_stickCheck = true;
		}
		if (!m_controler.fThumbLX)
		{
			m_stickCheck = false;
		}
		switch (m_count)
		{
		case 0:
			m_clearText1->SetColor(Col4(1, 0, 0, 1));
			m_clearText2->SetColor(Col4(1, 1, 1, 1));
			m_clearText3->SetColor(Col4(1, 1, 1, 1));
			break;
		case 1:
			m_clearText1->SetColor(Col4(1, 1, 1, 1));
			m_clearText2->SetColor(Col4(1, 0, 0, 1));
			m_clearText3->SetColor(Col4(1, 1, 1, 1));
			break;
		case 2:
			m_clearText1->SetColor(Col4(1, 1, 1, 1));
			m_clearText2->SetColor(Col4(1, 1, 1, 1));
			m_clearText3->SetColor(Col4(1, 0, 0, 1));
			break;
		}
		
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			if (m_count == 2)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//�^�C�g���V�[���Ɉړ�����
			}
			if (m_count == 1)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");//�Z���N�g�V�[���Ɉړ�����
			}
			if (m_count == 0)
			{
				switch (m_lastPlayStage)
				{
				case 1:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
					break;
				case 2:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage02");//�Q�[���V�[���Ɉړ�����
					break;
				case 3:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage03");//�Q�[���V�[���Ɉړ�����
					break;
				case 4:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage04");//�Q�[���V�[���Ɉړ�����
					break;
				case 5:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage05");//�Q�[���V�[���Ɉړ�����
					break;
				case 6:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage06");//�Q�[���V�[���Ɉړ�����
					break;
				case 7:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage07");//�Q�[���V�[���Ɉړ�����
					break;
				case 8:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage08");//�Q�[���V�[���Ɉړ�����
					break;
				case 9:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage09");//�Q�[���V�[���Ɉړ�����
					break;
				case 10:
					PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage10");//�Q�[���V�[���Ɉړ�����
					break;
				default:
					break;
				}
			}
		}
	}

	void GameOverStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);


	}

}
//end basecross
