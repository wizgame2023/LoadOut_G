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
		const Vec3 eye(0.0f, 100.0f, -100.0f);
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

	void YushinStage::CreateEnemy()
	{
		shared_ptr<Enemy> ptrEnemy = AddGameObject<Enemy>(Vec3(0.0f, 0.5f, 30.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(10.0f));
	}

	void YushinStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			CreateEnemy();
		}
		catch (...) {
			throw;
		}
	}

}
//end basecross
