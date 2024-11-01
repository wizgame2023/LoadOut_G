/*!
@file YushinStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void YushinStage::CreateViewLight() {
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


	void YushinStage::OnCreate() {
		try {
			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();
			AddGameObject<Enemy>();
			//Player�̐���
			auto ptrPlayer = AddGameObject<Player>(Vec3(50.0f, 5.0f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"Player", ptrPlayer);

			auto mapManager = AddGameObject<MapManager>();
			SetSharedGameObject(L"MapManager", mapManager);

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
