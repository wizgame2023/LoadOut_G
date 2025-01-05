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

		auto w = 250;
		auto h = 200;
		for (int i = 1; i < m_allStage + 1; i++)
		{
			if (i <= 5)
			{
				AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * i), 250.0f, 0.0f));
			}
			else if (i > 5 && i <= 10)
			{
				AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 5)), 250.0f - h, 0.0f));
			}
			else if (i > 10 && i <= 15)
			{
				AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 10)), 250.0f - h * 2, 0.0f));
			}
			else if(i>=15)
			{
				AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 15)), 250.0f - h * 3, 0.0f));
			}
		}
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
		auto m_controler = inputDevice.GetControlerVec()[0];


		if (m_controler.wButtons & XINPUT_GAMEPAD_B)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//�Q�[���V�[���Ɉړ�����
		}
	}

}
//end basecross
