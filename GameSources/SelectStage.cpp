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

		m_spriteMozi = AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.3f, 150 * 0.5f), Vec3(-500.0f, -350.0f, 0.0f));
		m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.3f, 150 * 0.5f), Vec3(-500.0f, -352.0f, 0.0f));
		m_spriteMozi->SetColor(Col4(0.3, 0.3, 0.3, 1));
		m_spriteB->SetColor(Col4(1, 0, 0, 1));

		//BGM
		auto bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = bgmManager->Start(L"SelectStageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		//暗転処理
		m_blackOut = AddGameObject<BlackOut>(false);


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
		m_controler = inputDevice.GetControlerVec()[0];

		//暗転が終わったらステージ移動
		if (m_blackOut->GetBlackOutFlag())
		{
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

		//決定したら選択するステージは動かないようにする
		if (m_decisionFlag) return;

		//ステージ移動処理
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Decision", 0, 0.9f);

			m_blackOut->SetSwitch(true);//暗転開始
			m_decisionFlag = true;//ステージ決定したことを伝える
		}

		//どのステージにするかのテクスチャの遷移処理
		SelectionStage();

	}

	void SelectStage::SelectionStage()
	{
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();//コントローラー取得

		//スティックを離したらまた受け取れるようにする
		if (cntlVec[0].fThumbLX == 0 && !m_stickCheck)
		{
			m_stickCheck = true;
		}
		//選択ステージの変更
		if (cntlVec[0].fThumbLX <= -0.9f && m_stickCheck)//左
		{
			if (m_SelectStage >= 2)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage--;
			}			
			if (m_SelectStage <= 1)
			{
				m_SelectStage = 10;
			}

			m_stickCheck = false;//スティックを受け取れないようにする
		}
		if (cntlVec[0].fThumbLX >= 0.9f && m_stickCheck)//右
		{
			if (m_SelectStage < 10)
			{
				auto SEManager = App::GetApp()->GetXAudio2Manager();
				auto SE = SEManager->Start(L"Choice", 0, 0.9f);
				m_SelectStage++;
			}
			if (m_SelectStage >= 10)
			{
				m_SelectStage = 1;
			}

			m_stickCheck = false;//スティックを受け取れないようにする
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

	}

}
//end basecross
