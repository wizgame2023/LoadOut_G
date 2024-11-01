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


	void YushinStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Enemy>();
			//Playerの生成
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
