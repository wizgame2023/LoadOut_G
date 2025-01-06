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
	void GameStage12::CreateViewLight() {
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

	void GameStage12::OnCreate() {
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

		//�Ō�Ƀv���C�����X�e�[�W��n��
		App::GetApp()->GetScene<Scene>()->SetLastPlayStage(12);

		//�}�b�v�}�l�[�W���[�̐���
		auto mapManager = AddGameObject<MapManager>(L"Stage01/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();

        //�R���W�����}�l�[�W���[�쐬
		auto collisionManager = AddGameObject<StageCollisionManager>();
		SetSharedGameObject(L"CollsionManager", collisionManager);		
		
		//�X�e�[�W�}�l�[�W���[����
		auto stageManager = AddGameObject<StageManager>();
		SetSharedGameObject(L"StageManager", stageManager);

		//�~�j�}�b�v�}�l�[�W������
		m_miniMapManager = AddGameObject<MiniMapManager>(mapSize);
		SetSharedGameObject(L"MiniMapManager", m_miniMapManager);

		//���̍쐬
		AddGameObject<Ground>();

		//�A�C�e���̐���//stage20
		//AddGameObject<Battery>(Vec3(-5.0f, 2.5f, -24.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(-25.0f, 2.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(-64.0f, 2.5f, 14.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(25.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(85.0f, 2.5f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(5.0f, 2.5f, -85.0f), Vec3(0.0f, 0.0f, 0.0f));
		CreateBattery();//�A�C�e���̐���

		m_miniMapManager->CreateBattery();

		//Player�̐���
		CreatePlayer();

		//�G����stage20
		//auto enemy = AddGameObject<Enemy>();
		//enemy->AddTag(L"Key");//���������Ă��邱�Ƃɂ���
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, -95.0f));
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, 95.0f));
		//AddGameObject<Enemy>(Vec3(-95.0f, 2.5f, -95.0f));
		CreateEnemy();
		m_miniMapManager->CreateEnemy();

		AddGameObject<MovieGameStart>(mapSize);//���[�r�[����
	}

	void GameStage12::OnUpdate()
	{
	}

	//Player����
	void GameStage12::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(45.0f, 3.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);
		m_miniMapManager->CreatePlayer();
	}

	//Enemy����
	void GameStage12::CreateEnemy()
	{
		vector<shared_ptr<Enemy>>enemyVec;
		vector<Vec3> posVec =
		{
			Vec3(-25.0f, 2.5f, -35.0f),
			Vec3(5.0f, 2.5f, 45.0f)
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			auto enemy = AddGameObject<Enemy>(posVec[i]);
			enemyVec.push_back(enemy);
		}
		enemyVec[0]->AddTag(L"Key");//���������Ă��邱�Ƃɂ���
	}

	//�A�C�e������
	void GameStage12::CreateBattery()
	{
		vector<Vec3> posVec =
		{
		   Vec3(-5.0f, 2.5f, -15.0f),//1
		   Vec3(-35.0f, 2.5f, -5.0f),//2
		   Vec3(-5.0f, 2.5f, 25.0f), //3
		   Vec3(45.0f, 2.5f, -15.0f),//4
		   Vec3(-45.0f, 2.5f, -45.0f)//5
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			AddGameObject<Battery>(posVec[i], Vec3(0.0f, 0.0f, 0.0f));
		}

	}

	//�G���ǂꂭ�炢�ǂ������Ă��邩�m�F����
	int GameStage12::GameEnemyState()
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

	void GameStage12::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


	void GameStage12::OutWallCreate(int selLength)//���X�̈����͂��̃}�b�v�̒��a�̓u���b�N���Ԃ񂩂𕷂��Ă��܂�
	{
		auto wall = AddGameObject<Wall>(Vec3((selLength * 10.0f) / 2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(-(selLength * 10.0f) / 2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength * 10) / 2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength * 10) / 2 + 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	}

	void GameStage12::SetEnemy(int num)
	{
		EnemyNow -= num;
	}
}
//end basecross
