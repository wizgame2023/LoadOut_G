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
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(0.0f, 80.0f, -60.0f));
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

		//マップマネージャーの生成
		auto mapManager = AddGameObject<MapManager>();
		SetSharedGameObject(L"MapManager", mapManager);
		mapManager->WallCreateKari();//仮の内壁を生成する

		//床の作成
		AddGameObject<Ground>();

		auto miniMapManager = AddGameObject<MiniMapManager>();//ミニマップ生成デバック用
		SetSharedGameObject(L"MiniMapManager", miniMapManager);

		//ブロックの作成
		for (int i = 0; i < 20; i++)
		{
			//AddGameObject<Block>(Vec3(-95.0f+(i*10), 5.0f, 95.0f), Vec3(0.0f, 0.0f, 0.0f));

		}

		//アイテムの生成
		AddGameObject<Item>(Vec3(-5.0f, 2.5f, -24.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(-25.0f, 2.5f, 45.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(-64.0f, 2.5f, 14.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(25.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(85.0f, 2.5f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Item>(Vec3(5.0f, 2.5f, -85.0f), Vec3(0.0f, 0.0f, 0.0f));
		miniMapManager->CreateItem();
		//Playerの生成
		auto player = AddGameObject<Player>(Vec3(35.0f, 3.0f, -45.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);

		//壁の生成
		//AddGameObject<Wall>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(20.0f,20.0f,20.0f));

		//マンホールの生成
		//AddGameObject<Manhole>(Vec3(20.0f, 4.0f, 10.0f));

		//BGM
		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		OutWallCreate(20);//外壁生成

		////中壁作成
		//{
		//	auto path = App::GetApp()->GetDataDirWString();
		//	auto levelPath = path + L"Levels/";
		//	vector<vector<int>> stageMap;

		//	ifstream ifs(levelPath += L"DebugStage.csv");
		//	if (ifs)
		//	{
		//		string line;
		//		while (getline(ifs, line))
		//		{
		//			vector<int> mapData;

		//			line += ",";
		//			string data;
		//			istringstream ss(line);
		//			while (getline(ss, data, ','))
		//			{
		//				int cellData = atoi(data.c_str());
		//				mapData.push_back(cellData);
		//			}

		//			stageMap.push_back(mapData);
		//		}
		//	}

		//	for (int r = 0; r < stageMap.size(); r++)
		//	{
		//		for (int c = 0; c < stageMap[0].size(); c++)
		//		{
		//			Vec3 startPos((c * 10.0f) - 95, 0.05f, 95 - (r * 10.0f));
		//			switch (stageMap[r][c])
		//			{
		//			case 1:
		//				AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(30.0, 10, 1.0));
		//				break;
		//			case 2:
		//				AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(1.0, 10, 30.0));
		//				break;
		//			}
		//		}
		//	}
		//}

		//敵生成
		AddGameObject<Enemy>();
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, -95.0f));

		AddGameObject<Enemy>(Vec3(95.0f, 2.5f, 95.0f));

		//AddGameObject<Enemy>(Vec3(-95.0f, 2.5f, -95.0f));

		miniMapManager->CreateEnemy();	


		

}

	void GameStage::OnUpdate()
	{
		GameManager();//ゲーム進行を管理する
	}

	//ゲームの進行を管理する後々関数ではなくクラスにします
	void GameStage::GameManager()
	{
		//ゲームクリアの条件
		//ステージのオブジェクトを全て取得
		auto obj = GetGameObjectVec();
		EnemyNow = 0;
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto manhole : obj)
		{

			if (dynamic_pointer_cast<Enemy>(manhole))//アイテム型にキャストする
			{

				auto a = 0;
				a++;
				EnemyNow = a;

			}
		}

		if (EnemyNow == 0)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//ゲームクリアに移動する
		}

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
