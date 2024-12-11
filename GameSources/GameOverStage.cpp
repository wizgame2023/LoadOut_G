/*!
@file GameOverStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void GameOverStage::CreateViewLight() {
		const Vec3 eye(0.0f, 5.0f, -5.0f);
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



	void GameOverStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Sprite>(L"GameOver", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f));//タイトル用のスプライト生成
		}
		catch (...) {
			throw;
		}

		//auto BGM = App::GetApp()->GetXAudio2Manager();
		//auto bgm = BGM->Start(L"GameOver", 0, 0.9f);

		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"GameOverBGM", 0, 0.9f);


		//SE生成マンホールにわなを仕掛ける音
		//auto SEManager = App::GetApp()->GetXAudio2Manager();
		//auto SE = SEManager->Start(L"SetManhole", 0, 0.9f);



	}



	void GameOverStage::OnUpdate()
	{
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		auto m_controler = inputDevice.GetControlerVec()[0];
		
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B||keyState.m_bPushKeyTbl[VK_SPACE])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//ゲームシーンに移動する
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_A||keyState.m_bPushKeyTbl['A'])
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//タイトルシーンに移動する
		}
	}

	void GameOverStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);


	}

}
//end basecross
