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

		//床の作成
		AddGameObject<Ground>();
		//ブロックの作成
		for (int i = 0; i < 20; i++)
		{
			AddGameObject<Block>(Vec3(-95.0f+(i*10), 5.0f, 95.0f), Vec3(0.0f, 0.0f, 0.0f));

		}
		
		//アイテムの生成
		AddGameObject<Item>(Vec3(15.0f,2.5f,0.0f),Vec3(0.0f,0.0f,0.0f));
		//Playerの生成
		AddGameObject<Player>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f));

		//壁の生成
		AddGameObject<Wall>(Vec3(0.0f, 5.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(20.0f,20.0f,20.0f));

		//マンホールの生成
		//AddGameObject<Manhole>(Vec3(20.0f, 4.0f, 10.0f));

		//外壁生成
		auto wall = AddGameObject<Wall>(Vec3(100.0f+0.5f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f),Vec3(200.0f,30.0f,1.0f));
		AddGameObject<Wall>(Vec3(-100.0f-0.5f, 0.0f, 0.0f), Vec3(0.0f, XMConvertToRadians(90.0f), 0.0f), Vec3(200.0f, 30.0f, 1.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, -100.0f-0.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(200.0f, 30.0f, 1.0f));
		AddGameObject<Wall>(Vec3(0.0f, 0.0f, 100.0f+0.5f), Vec3(0.0f, 0.0f, 0.0f), Vec3(200.0f, 30.0f, 1.0f));

	}

}
//end basecross
