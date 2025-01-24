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
	void GameStage09::CreateViewLight() {
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

	void GameStage09::OnCreate() {
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
		App::GetApp()->GetScene<Scene>()->SetLastPlayStage(9);

		//マップマネージャーの生成
		auto mapManager = AddGameObject<MapManager>(L"Stage09/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();

        //コリジョンマネージャー作成
		auto collisionManager = AddGameObject<StageCollisionManager>();
		SetSharedGameObject(L"CollsionManager", collisionManager);		
		
		//ステージマネージャー生成
		auto stageManager = AddGameObject<StageManager>();
		SetSharedGameObject(L"StageManager", stageManager);

		//ミニマップマネージャ生成
		m_miniMapManager = AddGameObject<MiniMapManager>(mapSize);
		SetSharedGameObject(L"MiniMapManager", m_miniMapManager);

		//床の作成
		AddGameObject<Ground>();

		//アイテムの生成
		CreateBattery();
		//ランダムアイテムの生成
		CreateRamdomItem();

		m_miniMapManager->CreateBattery();

		//Playerの生成
		CreatePlayer();

		//敵生成
		CreateEnemy();
		m_miniMapManager->CreateEnemy();

		stageManager->ClearMode(1);//特定の敵を倒すと鍵が手に入るモード

		AddGameObject<MovieGameStart>(mapSize);//ムービー生成
	}

	void GameStage09::OnUpdate()
	{
	}

	//Player生成
	void GameStage09::CreatePlayer()
	{
		auto player = AddGameObject<Player>(Vec3(40.0f, 3.0f, -40.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);
		m_miniMapManager->CreatePlayer();
	}

	//Enemy生成
	void GameStage09::CreateEnemy()
	{
		vector<shared_ptr<Enemy>>enemyVec;
		vector<Vec3> posVec =
		{
			Vec3(40.0f, 2.5f, 40.0f),
			Vec3(-60.0f, 2.5f, 30.0f),
			Vec3(-40.0f, 2.5f, -50.0f),
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			auto enemy = AddGameObject<Enemy>(posVec[i]);
			enemyVec.push_back(enemy);
		}
		//enemyVec[0]->AddTag(L"Key");//鍵を持っていることにする
	}

	//アイテム生成
	void GameStage09::CreateBattery()
	{
		vector<Vec3> posVec =
		{
		   Vec3(-40.0f, 2.5f, -30.0f),//1
		   Vec3(0.0f, 2.5f, 60.0f),//2
		   Vec3(50.0f, 2.5f, -50.0f), //3
		   Vec3(-30.0f, 2.5f, -40.0f),//4
		   Vec3(10.0f, 2.5f, -20.0f)//5
		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			AddGameObject<Battery>(posVec[i], Vec3(0.0f, 0.0f, 0.0f));
		}

	}

	//ランダムアイテム生成
	void GameStage09::CreateRamdomItem()
	{
		vector<Vec3> posVec =
		{
		   Vec3(30.0f, 2.5f, 40.0f),//1
		   Vec3(0.0f, 2.5f, -60.0f),//2

		};
		auto test = posVec.size();

		for (int i = 0; i < posVec.size(); i++)
		{
			AddGameObject<RandomItem>(posVec[i]);
		}

	}

	//敵がどれくらい追いかけてくるか確認する
	int GameStage09::GameEnemyState()
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

	void GameStage09::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);
	}


	void GameStage09::OutWallCreate(int selLength)//←個々の引数はこのマップの直径はブロック何個ぶんかを聞いています
	{
		auto wall = AddGameObject<Wall>(Vec3((selLength * 10.0f) / 2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(-(selLength * 10.0f) / 2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength * 10) / 2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength * 10) / 2 + 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	}

	void GameStage09::SetEnemy(int num)
	{
		EnemyNow -= num;
	}
}
//end basecross
