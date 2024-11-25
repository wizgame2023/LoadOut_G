/*!
@file GameStage.cpp
@brief �Q�[���X�e�[�W����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	�Q�[���X�e�[�W�N���X����
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 250.0f, -200.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//�r���[�̃J�����̐ݒ�
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//�}���`���C�g�̍쐬
		auto PtrMultiLight = CreateLight<MultiLight>();
		//�f�t�H���g�̃��C�e�B���O���w��
		PtrMultiLight->SetDefaultLighting();
	}



	void GameStage::OnCreate() {
		try 
		{
			//�w�i�̍쐬
			auto& app = App::GetApp();
			auto path = app->GetDataDirWString();

			auto happyskyPath = path + L"happysky/";
			for (const auto& keyName : happysky::pairs)
			{
				app->RegisterTexture(keyName.first, happyskyPath + keyName.first + L".png");
			}

			//�r���[�ƃ��C�g�̍쐬
			CreateViewLight();

			//�{�b�N�X
			AddGameObject<happysky>();

		}
		catch (...) {
			throw;
		}

		//�}�b�v�}�l�[�W���[�̐���
		auto mapManager = AddGameObject<MapManager>();
		SetSharedGameObject(L"MapManager", mapManager);
		mapManager->WallCreateKari();//���̓��ǂ𐶐�����

		//���̍쐬
		AddGameObject<Ground>();

		//auto miniMapManager = AddGameObject<MiniMapManager>();//�~�j�}�b�v�����f�o�b�N�p
		//SetSharedGameObject(L"MiniMapManager", miniMapManager);

		//�u���b�N�̍쐬
		for (int i = 0; i < 20; i++)
		{
			//AddGameObject<Block>(Vec3(-95.0f+(i*10), 5.0f, 95.0f), Vec3(0.0f, 0.0f, 0.0f));

		}

		//�A�C�e���̐���
		AddGameObject<Item>(Vec3(-5.0f, 2.5f, -24.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(-25.0f, 2.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(-64.0f, 2.5f, 14.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(25.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(85.0f, 2.5f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(5.0f, 2.5f, -85.0f), Vec3(0.0f, 0.0f, 0.0f));
		//miniMapManager->CreateItem();
		//Player�̐���
		auto player = AddGameObject<Player>(Vec3(35.0f, 3.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);

		//�ǂ̐���
		//AddGameObject<Wall>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(20.0f,20.0f,20.0f));

		//�}���z�[���̐���
		//AddGameObject<Manhole>(Vec3(20.0f, 4.0f, 10.0f));

		//BGM
		m_bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		

		OutWallCreate(20);//�O�ǐ���

		//�G����
		AddGameObject<Enemy>();
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, -95.0f));

		AddGameObject<Enemy>(Vec3(95.0f, 2.5f, 95.0f));

		//AddGameObject<Enemy>(Vec3(-95.0f, 2.5f, -95.0f));

		//miniMapManager->CreateEnemy();	

		////�����APlayer��ǂ������Ă���̂�1�l�ȏ�Ȃ�BGM��ς���
		//if (GameEnemyState() < 1)
		//{

		//}

		

	}

	void GameStage::OnUpdate()
	{
		GameManager();//�Q�[���i�s���Ǘ�����
	}

	int GameStage::GameEnemyState()
	{
		auto obj = GetGameObjectVec();
		auto EnemyTracking = 0;
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto enemy : obj)
		{
			auto enemycast = dynamic_pointer_cast<Enemy>(enemy);

			if (enemycast)//Enemy�^�ɃL���X�g�ɐ���������
			{
				auto State = enemycast->GetNowState();//���݂̃X�e�[�g���󂯎��
				auto trackcast = dynamic_pointer_cast<Tracking>(State);
				if (trackcast)//���݂̃X�e�[�g���g���b�L���O(�ǂ������鏈��)�̎�
				{
					EnemyTracking++;
				}
			}
		}

		return EnemyTracking;//�ǂ̂��炢�̐��̓G���ǂ������鏈�������Ă���̂��n��
	}

	//�Q�[���̐i�s���Ǘ������X�֐��ł͂Ȃ��N���X�ɂ��܂�
	void GameStage::GameManager()
	{
		//�Q�[���N���A�̏���
		//�X�e�[�W�̃I�u�W�F�N�g��S�Ď擾
		auto obj = GetGameObjectVec();
		EnemyNow = 0;
		//�擾�����I�u�W�F�N�g���A�C�e���ɕϊ��ł�����z��ɓ����
		for (auto manhole : obj)
		{

			if (dynamic_pointer_cast<Enemy>(manhole))//�A�C�e���^�ɃL���X�g����
			{

				auto a = 0;
				a++;
				EnemyNow = a;

			}
		}

		if (EnemyNow == 0)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//�Q�[���N���A�Ɉړ�����
		}

	}

	void GameStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


	void GameStage::OutWallCreate(int selLength)//���X�̈����͂��̃}�b�v�̒��a�̓u���b�N���Ԃ񂩂𕷂��Ă��܂�
	{
		auto wall = AddGameObject<Wall>(Vec3((selLength * 10.0f) / 2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(-(selLength * 10.0f) / 2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength * 10) / 2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength * 10) / 2 + 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	}

	void GameStage::SetEnemy(int num)
	{
		EnemyNow -= num;
	}


}
//end basecross
