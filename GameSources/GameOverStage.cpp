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
			AddGameObject<Sprite>(L"GameOverText", Vec2(800, 150), Vec3(0.0f, 300.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
			AddGameObject<Sprite>(L"GameClearTextAButton", Vec2(300, 100), Vec3(-200.0f, -350.0f, 0.0f));//�X�v���C�g����
			AddGameObject<Sprite>(L"GameClearTextBButton", Vec2(300, 100), Vec3(200.0f, -350.0f, 0.0f));//�X�v���C�g����

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


		//SE�����}���z�[���ɂ�Ȃ��d�|���鉹
		//auto SEManager = App::GetApp()->GetXAudio2Manager();
		//auto SE = SEManager->Start(L"SetManhole", 0, 0.9f);



	}



	void GameOverStage::OnUpdate()
	{
		//auto delta = App::GetApp()->GetElapsedTime();//�f���^�^�C��

		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//�L�[�{�[�h�f�o�b�N�p
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto m_controler = inputDevice.GetControlerVec()[0];

		////Player�̂��ꂵ���A�j���[�V����
		//auto player = GetSharedGameObject<Player>(L"Player");//�v���C���[�擾
		//auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		////Player�̃A�j���[�V�����X�V
		//playerDraw->UpdateAnimation(delta);

		
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B||keyState.m_bPushKeyTbl[VK_SPACE])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A||keyState.m_bPushKeyTbl['A'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//�^�C�g���V�[���Ɉړ�����
		}
	}

	void GameOverStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);


	}

}
//end basecross
