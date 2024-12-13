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
			m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -150.0f, 0.0f));
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
		if (m_controler.wButtons & XINPUT_GAMEPAD_B)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
		}
	}

}
//end basecross
