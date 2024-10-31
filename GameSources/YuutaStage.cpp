/*!
@file YuutaStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void YuutaStage::CreateViewLight() {
		const Vec3 eye(0.0f, 250.0f, -200.0f);
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



	void YuutaStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
		//�}�b�v�}�l�[�W���[�̐���
		auto mapManager = AddGameObject<MapManager>();
		SetSharedGameObject(L"MapManager", mapManager);

		//���̍쐬
		AddGameObject<Ground>();
		//�u���b�N�̍쐬
		for (int i = 0; i < 20; i++)
		{
			AddGameObject<Block>(Vec3(-95.0f+(i*10), 5.0f, 95.0f), Vec3(0.0f, 0.0f, 0.0f));

		}
		
		//�A�C�e���̐���
		AddGameObject<Item>(Vec3(15.0f,2.5f,0.0f),Vec3(0.0f,0.0f,0.0f));
		//Player�̐���
		AddGameObject<Player>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

		//�ǂ̐���
		AddGameObject<Wall>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(20.0f,20.0f,20.0f));

		//�}���z�[���̐���
		//AddGameObject<Manhole>(Vec3(20.0f, 4.0f, 10.0f));

		//�O�ǐ���
		auto wall = AddGameObject<Wall>(Vec3(100.0f+0.5f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(200.0f,30.0f,1.0f));
		AddGameObject<Wall>(Vec3(-100.0f-0.5f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(200.0f, 30.0f, 1.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, -100.0f-0.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(200.0f, 30.0f, 1.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, 100.0f+0.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(200.0f, 30.0f, 1.0f));

	}

}
//end basecross
