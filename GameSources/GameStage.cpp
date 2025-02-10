/*!
@file GameStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameStage::CreateViewLight() {
		const Vec3 eye(0.0f, 250.0f, -200.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 50.0f, -30.0f));
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void GameStage::OnCreate() {
		try 
		{
			//背景の作成
			auto& app = App::GetApp();
			auto path = app->GetDataDirWString();

			auto happyskyPath = path + L"happysky/";
			for (const auto& keyName : happysky::pairs)
			{
				app->RegisterTexture(keyName.first, happyskyPath + keyName.first + L".png");
			}

			//ビューとライトの作成
			CreateViewLight();

			//ボックス
			AddGameObject<happysky>();

		}
		catch (...) {
			throw;
		}
		//最後にプレイしたステージを渡す
		App::GetApp()->GetScene<Scene>()->SetLastPlayStage(1);

		//マップマネージャーの生成
		auto mapManager = AddGameObject<MapManager>(L"Stage01/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();

        //コリジョンマネージャー作成
		auto collisionManager = AddGameObject<StageCollisionManager>();
		SetSharedGameObject(L"CollsionManager", collisionManager);		
		
		//ステージマネージャー生成
		auto stageManager = AddGameObject<StageManager>(3,15.0f,10.0f);
		SetSharedGameObject(L"StageManager", stageManager);

		//ミニマップマネージャ生成
		m_miniMapManager = AddGameObject<MiniMapManager>(mapSize);
		SetSharedGameObject(L"MiniMapManager", m_miniMapManager);

		//床の作成
		AddGameObject<Ground>();

		//アイテムの生成//stage20
		CreateBattery();//アイテムの生成

		m_miniMapManager->CreateBattery();

		//Playerの生成
		CreatePlayer();

		//敵生成
		CreateEnemy();
		m_miniMapManager->CreateEnemy();
		stageManager->ClearMode(2,1);//クリア条件を決める

		AddGameObject<UIManager>();

		AddGameObject<MovieGameStart>(mapSize);//ムービー生成
	}

	void GameStage::OnUpdate()
	{
		//GetSharedGameObject<StageManager>(L"StageManager")->ClearMode(2);//クリア条件を決める
	}

	//Player生成
	void GameStage::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(45.0f, 0.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);
		m_miniMapManager->CreatePlayer();
	}

	//Enemy生成
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
		//enemyVec[0]->AddTag(L"Key");//鍵を持っていることにする
	}

	//アイテム生成
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

	//ランダムアイテム生成
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


	//敵がどれくらい追いかけてくるか確認する
	int GameStage::GameEnemyState()
	{
		auto obj = GetGameObjectVec();
		auto EnemyTracking = 0;
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto enemy : obj)
		{
			auto enemycast = dynamic_pointer_cast<Enemy>(enemy);

			if (enemycast)//Enemy型にキャストに成功したら
			{
				auto State = enemycast->GetNowState();//現在のステートを受け取る
				auto trackcast = dynamic_pointer_cast<Tracking>(State);
				if (trackcast)//現在のステートがトラッキング(追いかける処理)の時
				{
					EnemyTracking++;
				}
			}
		}

		return EnemyTracking;//どのくらいの数の敵が追いかける処理をしているのか渡す
	}

	void GameStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


	void GameStage::OutWallCreate(int selLength)//←個々の引数はこのマップの直径はブロック何個ぶんかを聞いています
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
