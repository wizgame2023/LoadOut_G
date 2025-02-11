/*!
@file GameExplanation.cpp
@brief �����p�̃Q�[���I�u�W�F�N�g
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameExplanation::GameExplanation(shared_ptr<Stage>& ptrStage) :
		GameObject(ptrStage),
		m_countPage(1)
	{
	}

	GameExplanation::~GameExplanation()
	{
	}

	void GameExplanation::OnCreate()
	{
		m_stage = GetStage();
		m_selectStage = dynamic_pointer_cast<SelectStage>(m_stage);
		if (m_selectStage)
		{
			m_selectStage->SetUpdateFlag(false);//�Z���N�g�X�e�[�W�̃A�b�v�f�[�g���Ȃ�
			
			//�w�i�X�v���C�g
			auto sprite = m_stage->AddGameObject<Sprite>(L"Black", Vec2(1280.0f, 800.0f), Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 0.8f), 2);
			m_spriteVec.push_back(sprite);//�z��ɓ����
		}

		//�߂�p�X�v���C�g
		auto sprite = m_stage->AddGameObject<Sprite>(L"BackMozi", Vec2(900 * 0.2f, 150 * 0.4f), Vec3(600.0f, -380.0f, 0.0f), Vec3(0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f),4);
		m_spriteVec.push_back(sprite);//�z��ɓ����
		sprite = m_stage->AddGameObject<Sprite>(L"AButton", Vec2(900 * 0.2f, 150 * 0.4f), Vec3(600.0f, -382.0f, 0.0f), Vec3(0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 5);
		m_spriteVec.push_back(sprite);//�z��ɓ����

		//�^�C�g������
		m_spriteTitle = m_stage->AddGameObject<Sprite>(L"GameExplanationTex0", Vec2(800.0f, 300.0f), Vec3(0.0f, 300.0f, 0.0f),
									Vec3(0.0f, 0.0f, 0.0f),Col4(1.0f,1.0f,1.0f,1.0f),3);
		m_spriteVec.push_back(m_spriteTitle);//�z��ɓ����

		//�����X�v���C�g
		m_spriteInfo = m_stage->AddGameObject<Sprite>(L"GameExplanationTex1", Vec2(1200.0f, 600.0f), Vec3(0.0f, -80.0f, 0.0f),
			Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 3);
		m_spriteVec.push_back(m_spriteInfo);//�z��ɓ����

		//�X�e�B�b�N�e�N�X�`��(��)
		sprite = m_stage->AddGameObject<Sprite>(L"LeftArrow", Vec2(50.0f, 50.0f), Vec3(-600.0f, -100.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 4);
		m_spriteVec.push_back(sprite);//�z��ɓ����
		//�X�e�B�b�N�e�N�X�`��(�E)
		sprite = m_stage->AddGameObject<Sprite>(L"RightArrow", Vec2(50.0f, 50.0f), Vec3(600.0f, -100.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 4);
		m_spriteVec.push_back(sprite);//�z��ɓ����
	}

	//�X�V
	void GameExplanation::OnUpdate()
	{
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		m_controler = inputDevice.GetControlerVec()[0];
		
		//�y�[�W�J�ڂ̏���
		SelectionPage();

		//�y�[�W�ɂ���ăe�N�X�`�����ς��
		switch (m_countPage)
		{
		case 1:
			m_spriteInfo->SetTexture(L"GameExplanationTex1");
			break;
		case 2:
			m_spriteInfo->SetTexture(L"GameExplanationTex2");
			break;
		case 3:
			m_spriteInfo->SetTexture(L"GameExplanationTex3");
			break;
		default:
			break;
		}

		//B�{�^����������I��
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			//�������g���폜
			m_stage->RemoveGameObject<GameExplanation>(GetThis<GameExplanation>());

			//�����ō�����X�v���C�g�����ׂč폜����
			for (auto sprite : m_spriteVec)
			{
				auto sharedSprite = sprite.lock();
				if (sharedSprite)
				{
					m_stage->RemoveGameObject<Sprite>(sharedSprite);//�X�v���C�g�폜
				}
			}
		}
	}

	//�������ꂽ��
	void GameExplanation::OnDestroy()
	{
		if (m_selectStage)
		{
			m_selectStage->SetUpdateFlag(true);//�Z���N�g�X�e�[�W�̃A�b�v�f�[�g�𕜊�
		}

	}
	
	//�y�[�W�J�ڂ̏���
	void GameExplanation::SelectionPage()
	{
		//�X�e�B�b�N�𗣂�����܂��󂯎���悤�ɂ���
		if (m_controler.fThumbLX == 0 && !m_stickCheck)
		{
			//������
			m_stickCheck = true;
		}
		else if (m_stickCheck)
		{
			if (m_controler.fThumbLX <= -0.9f && m_stickCheck)//��
			{
				if (m_countPage > 1)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage--;
				}
				else if (m_countPage == 1)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage = 3;
				}
				m_stickCheck = false;//�X�e�B�b�N���󂯎��Ȃ��悤�ɂ���
			}
			if (m_controler.fThumbLX >= 0.9f && m_stickCheck)//�E
			{
				if (m_countPage < 3)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage++;
				}
				else if (m_countPage == 3)
				{
					auto SEManager = App::GetApp()->GetXAudio2Manager();
					auto SE = SEManager->Start(L"Choice", 0, 0.9f);
					m_countPage = 1;
				}
				m_stickCheck = false;//�X�e�B�b�N���󂯎��Ȃ��悤�ɂ���
			}
		}
	}
}
//end basecross
