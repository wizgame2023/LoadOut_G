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
		//�Ō�Ƀv���C�����X�e�[�W��n��
		App::GetApp()->GetScene<Scene>()->SetLastPlayStage(1);

		//�}�b�v�}�l�[�W���[�̐���
		auto mapManager = AddGameObject<MapManager>(L"Stage01/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();

        //�R���W�����}�l�[�W���[�쐬
		auto collisionManager = AddGameObject<StageCollisionManager>();
		SetSharedGameObject(L"CollsionManager", collisionManager);		
		
		//�X�e�[�W�}�l�[�W���[����
		auto stageManager = AddGameObject<StageManager>(3,15.0f,10.0f);
		SetSharedGameObject(L"StageManager", stageManager);

		//�~�j�}�b�v�}�l�[�W������
		m_miniMapManager = AddGameObject<MiniMapManager>(mapSize);
		SetSharedGameObject(L"MiniMapManager", m_miniMapManager);

		//���̍쐬
		AddGameObject<Ground>();

		//�A�C�e���̐���//stage20
		CreateBattery();//�A�C�e���̐���

		m_miniMapManager->CreateBattery();

		//Player�̐���
		CreatePlayer();

		//�G����
		CreateEnemy();
		m_miniMapManager->CreateEnemy();
		stageManager->ClearMode(2,1);//�N���A���������߂�

		AddGameObject<UIManager>();

		AddGameObject<MovieGameStart>(mapSize);//���[�r�[����
	}

	void GameStage::OnUpdate()
	{
		//GetSharedGameObject<StageManager>(L"StageManager")->ClearMode(2);//�N���A���������߂�
	}

	//Player����
	void GameStage::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(45.0f, 0.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);
		m_miniMapManager->CreatePlayer();
	}

	//Enemy����
	void GameStage::CreateEnemy()
	{
		vector<shared_ptr<Enemy>>enemyVec;
		vector<Vec3> posVec =
		{
			Vec3(-25.0f, 0.0f, -35.0f),
			Vec3(5.0f, 0.0f, 45.0f)
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			auto enemy = AddGameObject<Enemy>(posVec[i],true, normal);
			enemyVec.push_back(enemy);
		}
		//enemyVec[0]->AddTag(L"Key");//���������Ă��邱�Ƃɂ���
	}

	//�A�C�e������
	void GameStage::CreateBattery()
	{
		vector<Vec3> posVec =
		{
		   Vec3(-5.0f, 2.5f, -15.0f),//1
		   Vec3(-35.0f, 2.5f, -5.0f),//2
		   Vec3(-5.0f, 2.5f, 25.0f), //3
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			AddGameObject<Battery>(posVec[i], Vec3(0.0f, 0.0f, 0.0f));
		}

	}

	//�����_���A�C�e������
	void GameStage::CreateRamdomItem()
	{
		vector<Vec3> posVec =
		{
		   Vec3(-5.0f, 2.5f, -15.0f),//1
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			AddGameObject<RandomItem>(posVec[i]);
		}

	}


	//�G���ǂꂭ�炢�ǂ������Ă��邩�m�F����
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
