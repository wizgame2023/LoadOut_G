/*!
@file TilteStage.cpp
@brief ゲームステージ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	//	ゲームステージクラス実体
	//--------------------------------------------------------------------------------------
	void SelectStage::CreateViewLight() {
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



	void SelectStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
		}
		catch (...) {
			throw;
		}
		//xが１２８０ｙが８００
		AddGameObject<Sprite>(L"BackGround", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f),0);//タイトル用のスプライト生成
		m_StagePhoto = AddGameObject<Sprite>(L"Stage01_HiShot", Vec2(900, 500), Vec3(0.0f, 100.0f, 0.0f));//タイトル用のスプライト生成
		m_StageText = AddGameObject<Sprite>(L"StageText", Vec2(800, 150), Vec3(-120.0f, -300.0f, 0.0f));//タイトル用のスプライト生成
		m_NumberSprite = AddGameObject<NuberManager>(1, Vec2(150, 150), Vec3(+260, -300.0f, 0.0f),true,80.0f);
		m_StageText = AddGameObject<Sprite>(L"RightArrow", Vec2(200, 200), Vec3(550.0f, 0.0f, 0.0f));//タイトル用のスプライト生成
		m_StageText = AddGameObject<Sprite>(L"LeftArrow", Vec2(200, 200), Vec3(-550.0f, 0.0f, 0.0f));//タイトル用のスプライト生成

		//BGM
		auto bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = bgmManager->Start(L"SelectStageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);


		//auto w = 250;
		//auto h = 200;
		//for (int i = 1; i < m_allStage + 1; i++)
		//{
		//	if (i <= 5)
		//	{
		//		AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * i), 250.0f, 0.0f));
		//	}
		//	else if (i > 5 && i <= 10)
		//	{
		//		AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 5)), 250.0f - h, 0.0f));
		//	}
		//	else if (i > 10 && i <= 15)
		//	{
		//		AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 10)), 250.0f - h * 2, 0.0f));
		//	}
		//	else if(i>=15)
		//	{
		//		AddGameObject<NuberManager>(i, Vec2(50, 50), Vec3((-500 - w) + (w * (i - 15)), 250.0f - h * 3, 0.0f));
		//	}
		//}
		m_SelectStage = 1;
	}

	void SelectStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);

	}

	void SelectStage::OnUpdate()
	{
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		auto m_controler = inputDevice.GetControlerVec()[0];

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)//L
		{
			if (m_SelectStage <= 1)
			{
				//ぶぶーのSE
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Error", 0, 0.9f);
			}
			if (m_SelectStage >= 2)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage--;
			}
		}
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)//R
		{
			if (m_SelectStage >= 10)
			{
				//ぶぶーのSE
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Error", 0, 0.9f);
			}
			if (m_SelectStage < 10)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage++;
			}
		}

		//テクスチャ変更
		switch (m_SelectStage)
		{
		case 1:
			m_StagePhoto->SetTexture(L"Stage01_HiShot");
			m_NumberSprite->SetNum(1);
			break;
		case 2:
			m_StagePhoto->SetTexture(L"Stage02_HiShot");
			m_NumberSprite->SetNum(2);
			break;
		case 3:
			m_StagePhoto->SetTexture(L"Stage03_HiShot");
			m_NumberSprite->SetNum(3);
			break;
		case 4:
			m_StagePhoto->SetTexture(L"Stage04_HiShot");
			m_NumberSprite->SetNum(4);
			break;
		case 5:
			m_StagePhoto->SetTexture(L"Stage05_HiShot");
			m_NumberSprite->SetNum(5);
			break;
		case 6:
			m_StagePhoto->SetTexture(L"Stage06_HiShot");
			m_NumberSprite->SetNum(6);
			break;
		case 7:
			m_StagePhoto->SetTexture(L"Stage07_HiShot");
			m_NumberSprite->SetNum(7);
			break;
		case 8:
			m_StagePhoto->SetTexture(L"Stage08_HiShot");
			m_NumberSprite->SetNum(8);
			break;
		case 9:
			m_StagePhoto->SetTexture(L"Stage09_HiShot");
			m_NumberSprite->SetNum(9);
			break;
		case 10:
			m_StagePhoto->SetTexture(L"Stage10_HiShot");
			m_NumberSprite->SetNum(10);
			break;
		default:
			break;
		}

		//ステージ移動処理
		if (m_controler.wButtons & XINPUT_GAMEPAD_B)
		{
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Decision", 0, 0.9f);

			switch (m_SelectStage)
			{
			case 1:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//ゲームシーンに移動する
				break;
			case 2:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage02");//ゲームシーンに移動する
				break;
			case 3:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage03");//ゲームシーンに移動する
				break;
			case 4:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage04");//ゲームシーンに移動する
				break;
			case 5:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage05");//ゲームシーンに移動する
				break;
			case 6:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage06");//ゲームシーンに移動する
				break;
			case 7:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage07");//ゲームシーンに移動する
				break;
			case 8:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage08");//ゲームシーンに移動する
				break;
			case 9:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage09");//ゲームシーンに移動する
				break;
			case 10:
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage10");//ゲームシーンに移動する
				break;
			default:
				break;
			}
		}
	}

}
//end basecross
