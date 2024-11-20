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
		auto PtrCamera = ObjectFactory::Create<Camera>();
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
			AddGameObject<Sprite>(L"GameOver", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f));//�^�C�g���p�̃X�v���C�g����
		}
		catch (...) {
			throw;
		}

		//auto BGM = App::GetApp()->GetXAudio2Manager();
		//BGM->Start(L"GameOver", 0, 0.9f);


	}



	void GameOverStage::OnUpdate()
	{
		// �C���v�b�g�f�o�C�X�I�u�W�F�N�g
		auto inputDevice = App::GetApp()->GetInputDevice(); // �l�X�ȓ��̓f�o�C�X���Ǘ����Ă���I�u�W�F�N�g���擾
		//�R���g���[���[�̃A�i���O�X�e�B�b�N�̌���
		auto m_controler = inputDevice.GetControlerVec()[0];

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//�^�C�g���V�[���Ɉړ�����
		}
	}

}
//end basecross
