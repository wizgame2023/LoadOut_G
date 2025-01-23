/*!
@file TilteStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void SelectStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
		//x���P�Q�W�O�����W�O�O
		AddGameObject<Sprite>(L"BackGround", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f),0);//�^�C�g���p�̃X�v���C�g����
		m_StagePhoto = AddGameObject<Sprite>(L"Stage01_HiShot", Vec2(900, 500), Vec3(0.0f, 100.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
		m_StageText = AddGameObject<Sprite>(L"StageText", Vec2(800, 150), Vec3(-120.0f, -300.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
		m_NumberSprite = AddGameObject<NuberManager>(1, Vec2(150, 150), Vec3(+260, -300.0f, 0.0f),true,80.0f);
		m_StageText = AddGameObject<Sprite>(L"RightArrow", Vec2(200, 200), Vec3(550.0f, 0.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
		m_StageText = AddGameObject<Sprite>(L"LeftArrow", Vec2(200, 200), Vec3(-550.0f, 0.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����

		m_spriteMozi = AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.3f, 150 * 0.5f), Vec3(-500.0f, -350.0f, 0.0f));
		m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.3f, 150 * 0.5f), Vec3(-500.0f, -352.0f, 0.0f));
		m_spriteMozi->SetColor(Col4(0.3, 0.3, 0.3, 1));
		m_spriteB->SetColor(Col4(1, 0, 0, 1));

		//BGM
		auto bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = bgmManager->Start(L"SelectStageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		//�Ó]����
		m_blackOut = AddGameObject<BlackOut>(false);


		m_SelectStage = 1;
	}

	void SelectStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}

	void SelectStage::OnUpdate()
	{
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		m_controler = inputDevice.GetControlerVec()[0];

		//�Ó]���I�������X�e�[�W�ړ�
		if (m_blackOut->GetBlackOutFlag())
		{
			switch (m_SelectStage)
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

		//���肵����I������X�e�[�W�͓����Ȃ��悤�ɂ���
		if (m_decisionFlag) return;

		//�X�e�[�W�ړ�����
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Decision", 0, 0.9f);

			m_blackOut->SetSwitch(true);//�Ó]�J�n
			m_decisionFlag = true;//�X�e�[�W���肵�����Ƃ�`����
		}

		//�ǂ̃X�e�[�W�ɂ��邩�̃e�N�X�`���̑J�ڏ���
		SelectionStage();

	}

	void SelectStage::SelectionStage()
	{
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//�R���g���[���[�擾

		//�X�e�B�b�N�𗣂�����܂��󂯎���悤�ɂ���
		if (cntlVec[0].fThumbLX == 0 && !m_stickCheck)
		{
			m_stickCheck = true;
		}
		//�I���X�e�[�W�̕ύX
		if (cntlVec[0].fThumbLX <= -0.9f && m_stickCheck)//��
		{
			if (m_SelectStage >= 2)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage--;
			}			
			if (m_SelectStage <= 1)
			{
				m_SelectStage = 10;
			}

			m_stickCheck = false;//�X�e�B�b�N���󂯎��Ȃ��悤�ɂ���
		}
		if (cntlVec[0].fThumbLX >= 0.9f && m_stickCheck)//�E
		{
			if (m_SelectStage < 10)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage++;
			}
			if (m_SelectStage >= 10)
			{
				m_SelectStage = 1;
			}

			m_stickCheck = false;//�X�e�B�b�N���󂯎��Ȃ��悤�ɂ���
		}

		//�e�N�X�`���ύX
		switch (m_SelectStage)
		{
		case 1:
			m_StagePhoto->SetTexture(L"Stage01_HiShot");
			m_NumberSprite->SetNum(1);
			break;
		case 2:
			m_StagePhoto->SetTexture(L"Stage02_HiShot");
			m_NumberSprite->SetNum(2);
			break;
		case 3:
			m_StagePhoto->SetTexture(L"Stage03_HiShot");
			m_NumberSprite->SetNum(3);
			break;
		case 4:
			m_StagePhoto->SetTexture(L"Stage04_HiShot");
			m_NumberSprite->SetNum(4);
			break;
		case 5:
			m_StagePhoto->SetTexture(L"Stage05_HiShot");
			m_NumberSprite->SetNum(5);
			break;
		case 6:
			m_StagePhoto->SetTexture(L"Stage06_HiShot");
			m_NumberSprite->SetNum(6);
			break;
		case 7:
			m_StagePhoto->SetTexture(L"Stage07_HiShot");
			m_NumberSprite->SetNum(7);
			break;
		case 8:
			m_StagePhoto->SetTexture(L"Stage08_HiShot");
			m_NumberSprite->SetNum(8);
			break;
		case 9:
			m_StagePhoto->SetTexture(L"Stage09_HiShot");
			m_NumberSprite->SetNum(9);
			break;
		case 10:
			m_StagePhoto->SetTexture(L"Stage10_HiShot");
			m_NumberSprite->SetNum(10);
			break;
		default:
			break;
		}

	}

}
//end basecross
