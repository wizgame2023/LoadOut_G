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
	void TilteStage::CreateViewLight() {
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



	void TilteStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Sprite>(L"Title", Vec2(1280,800), Vec3(0.0f, 0.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
			m_spriteMozi = AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -150.0f, 0.0f));
			m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -152.0f, 0.0f));
			AddGameObject<Sprite>(L"CreditMozi", Vec2(256*0.5, 128*0.5), Vec3(570.0f, -370.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
			m_Credit = AddGameObject<Sprite>(L"Credit", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f));//�N���W�b�g����
			m_break = AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0.0f));
			m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
			m_break->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));


		}
		catch (...) {
			throw;
		}

		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"TIlteStage", 0, 0.9f);

	}

	void TilteStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);

	}

	void TilteStage::OnUpdate()
	{
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//�L�[�{�[�h�f�o�b�N�p

		auto time = App::GetApp()->GetElapsedTime();
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto m_controler = inputDevice.GetControlerVec()[0];

		if (m_transparency > 0.0f && !m_transparent)
		{
			m_transparency -= 1.0f * App::GetApp()->GetElapsedTime();
		}
		if (m_transparency < 1 && m_transparent)
		{
			m_transparency += 1.0f * App::GetApp()->GetElapsedTime();
		}

		if (m_transparency <= 0)
		{
			m_transparent = true;
		}
		if (m_transparency >= 1)
		{
			m_transparent = false;
		}

		m_spriteMozi->SetColor(Col4(0.3, 0.3, 0.3, m_transparency));
		m_spriteB->SetColor(Col4(1, 0, 0, m_transparency));

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B || keyState.m_bPushKeyTbl[VK_SPACE])
		{
			m_onFaed = true;
		}
		if (m_onFaed)
		{
			float fadeSpeed = 1.0f;

			m_anCollar += fadeSpeed * time;

			m_break->SetColor(Col4(1, 1, 1, m_anCollar));
			if (m_anCollar>=1.0f)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
			}
		}

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_X)
		{
			if (m_creditCount)
			{
				m_creditCount = false;
				m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (!m_creditCount)
			{
				m_creditCount = true;
				m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}

}
//end basecross
