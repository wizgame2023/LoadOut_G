/*!
@file YuutaStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void YuutaStage::CreateViewLight() {
		const Vec3 eye(0.0f, 300.0f, -200.0f);
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



	void YuutaStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
		//マップマネージャーの生成
		auto mapManager = AddGameObject<MapManager>();
		SetSharedGameObject(L"MapManager", mapManager);
		//mapManager->WallCreateKari();//仮の内壁を生成する

		//床の作成
		AddGameObject<Ground>();
		//ブロックの作成
		for (int i = 0; i < 20; i++)
		{
			AddGameObject<Block>(Vec3(-95.0f+(i*10), 5.0f, 95.0f), Vec3(0.0f, 0.0f, 0.0f));

		}
		AddGameObject<Enemy>();

		auto miniMapManager = AddGameObject<MiniMapManager>();//ミニマップ生成デバック用
		SetSharedGameObject(L"MiniMapManager", miniMapManager);
		
		//アイテムの生成
		AddGameObject<Battery>(Vec3(15.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Battery>(Vec3(50.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Battery>(Vec3(-50.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Battery>(Vec3(-10.0f, 2.5f, 50.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Battery>(Vec3(-10.0f, 2.5f, 25.0f), Vec3(0.0f, 0.0f, 0.0f));
		AddGameObject<Battery>(Vec3(-10.0f, 2.5f, -50.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(10.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(20.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(25.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//AddGameObject<Battery>(Vec3(30.0f, 2.5f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		//Playerの生成
		auto player = AddGameObject<Player>(Vec3(0.0f, 3.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));
		SetSharedGameObject(L"Player", player);

		//壁の生成
		//AddGameObject<Wall>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(20.0f,20.0f,20.0f));

		//マンホールの生成
		//AddGameObject<Manhole>(Vec3(20.0f, 4.0f, 10.0f));

		//AddGameObject<RaySphere>();


		AddGameObject<ClearObject>(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));//透明壁生成


		//AddGameObject<SpriteNum>(L"Number",Vec2(30.0f,30.0f),10,Vec3(500.0f,0.0f,0.0f));//数字のスプライト生成

		miniMapManager->CreateBattery();

		OutWallCreate(20);//外壁生成
	}

	void YuutaStage::OutWallCreate(int selLength)//←個々の引数はこのマップの直径はブロック何個ぶんかを聞いています
	{

		auto wall = AddGameObject<Wall>(Vec3((selLength*10.0f)/2 + 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(0.0f,0.0f,0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(-(selLength*10.0f)/2 - 1.0f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (-selLength*10)/2 - 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, (selLength*10)/2+ 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3((selLength * 10.0f), 30.0f, 2.0f));

	}

}
//end basecross
