/*!
@file GameClearStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameClearStage::CreateViewLight() {
		const Vec3 eye(0.0f, 100.0f, -30.0f);
		const Vec3 at(0.0f);
		auto PtrView = CreateView<SingleView>();
		//ビューのカメラの設定
		auto PtrCamera = ObjectFactory::Create<MyCamera>(Vec3(2.0f, 10.0f, -10.0f));
		PtrView->SetCamera(PtrCamera);
		PtrCamera->SetEye(eye);
		PtrCamera->SetAt(at);
		//マルチライトの作成
		auto PtrMultiLight = CreateLight<MultiLight>();
		//デフォルトのライティングを指定
		PtrMultiLight->SetDefaultLighting();
	}



	void GameClearStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			//AddGameObject<Sprite>(L"GameClear", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f));//タイトル用のスプライト生成
			AddGameObject<Sprite>(L"GameClearText", Vec2(800, 150), Vec3(0.0f, 300.0f, 0.0f));//タイトル用のスプライト生成
			AddGameObject<Sprite>(L"GameClearTextAButton", Vec2(300, 100), Vec3(-200.0f, -350.0f, 0.0f));//タイトル用のスプライト生成
			AddGameObject<Sprite>(L"GameClearTextBButton", Vec2(300, 100), Vec3(200.0f, -350.0f, 0.0f));//タイトル用のスプライト生成
		}
		catch (...) {
			throw;
		}

		//マップマネージャーの生成
		auto mapManager = AddGameObject<MapManager>(L"ClearStage/");
		SetSharedGameObject(L"MapManager", mapManager);
		auto mapSize = mapManager->GetMapSize();


		auto player = AddGameObject<Player>(Vec3(5.0f, 0.0f, 25.0f),Vec3(0.0f,XMConvertToRadians(90.0f), 0.0f), false);
		SetSharedGameObject(L"Player",player);
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		playerDraw->ChangeCurrentAnimation(L"Happey");//うれしいモーションに変更


		//床の作成
		AddGameObject<Ground>();


		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"GameClear2", 0, 0.9f);

	}

	void GameClearStage::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();//デルタタイム

		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		auto m_controler = inputDevice.GetControlerVec()[0];

		//Playerのうれしいアニメーション
		auto player = GetSharedGameObject<Player>(L"Player");//プレイヤー取得
		auto playerDraw = player->GetComponent<PNTBoneModelDraw>();
		//Playerのアニメーション更新
		playerDraw->UpdateAnimation(delta);


		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//ゲームシーンに移動する
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B||keyState.m_bPushKeyTbl[VK_SPACE])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//タイトルシーンに移動する
		}
	}


	void GameClearStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);


	}

}
//end basecross
