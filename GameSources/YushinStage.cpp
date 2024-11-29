/*!
@file YushinStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void YushinStage::CreateViewLight() {
		const Vec3 eye(0.0f, 250.0f, -200.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<Camera>();
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}

	void YushinStage::CreateWall()
	{
		//auto path = App::GetApp()->GetDataDirWString();
		//auto levelPath = path + L"Levels/";
		//vector<vector<int>> stageMap;

		//ifstream ifs(levelPath += L"DebugStage.csv");
		//if (ifs)
		//{
		//	string line;
		//	while (getline(ifs, line))
		//	{
		//		vector<int> mapData;

		//		line += ",";
		//		string data;
		//		istringstream ss(line);
		//		while (getline(ss, data, ','))
		//		{
		//			int cellData = atoi(data.c_str());
		//			mapData.push_back(cellData);
		//		}

		//		stageMap.push_back(mapData);
		//	}
		//}

		//for (int r = 0; r < stageMap.size(); r++)
		//{
		//	for (int c = 0; c < stageMap[0].size(); c++)
		//	{
		//		Vec3 startPos((c * 10.0f) - 95, 0.05f, 95 - (r * 10.0f));
		//		switch (stageMap[r][c])
		//		{
		//		case 1:
		//			AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(30.0, 10, 1.0));
		//			break;
		//		case 2:
		//			AddGameObject<Wall>(startPos, Vec3(0, 0, 0), Vec3(1.0, 10, 30.0));
		//			break;
		//		}
		//	}
		//}
	auto selLength = 20;
	auto wall = AddGameObject<Wall>(Vec3((selLength * 10.0f) / 2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(-(selLength * 10.0f) / 2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength * 10) / 2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
	AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength * 10) / 2 + 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));

	}

	void YushinStage::CreateEnemy()
	{
		//AddGameObject<Enemy>(Vec3(0.0f, 2.5f, 0.0f));
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, -95.0f));
		//AddGameObject<Enemy>(Vec3(95.0f, 2.5f, 95.0f));
		//AddGameObject<Enemy>(Vec3(-95.0f, 2.5f, -95.0f));
		auto group = CreateSharedObjectGroup(L"SeekGroup");
		//配列の初期化
		vector<Vec3> vec = {
			{ -95.0f, 2.5f, 95.0f },
		};

		//配置オブジェクトの作成
		for (size_t count = 0; count < vec.size(); count++) {
			auto ptr = AddGameObject<Enemy>(vec[count]);
			//ナンバースクエアを作成して関連させる
			AddGameObject<NumberSquare>(ptr, count);
		}


	}
	void YushinStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			auto miniMapManager = AddGameObject<MiniMapManager>();//ミニマップ生成デバック用
			SetSharedGameObject(L"MiniMapManager", miniMapManager);
			//Playerの生成
			auto ptrPlayer = AddGameObject<Player>(Vec3(50.0f, 3.0f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
			SetSharedGameObject(L"Player", ptrPlayer);
			CreateWall();
			AddGameObject<Ground>();
			auto mapManager = AddGameObject<MapManager>();
			SetSharedGameObject(L"MapManager", mapManager);
			//mapManager->WallCreateKari();//仮の内壁を生成する

			CreateEnemy();

		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
