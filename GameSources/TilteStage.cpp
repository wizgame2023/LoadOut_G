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
	void TilteStage::CreateViewLight() {
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



	void TilteStage::OnCreate() {
		try {
			//ビューとライトの作成
			CreateViewLight();
			AddGameObject<Sprite>(L"Title", Vec2(1280,800), Vec3(0.0f, 0.0f, 0.0f));//タイトル用のスプライト生成

			m_spriteMozi = AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -200.0f, 0.0f));
			m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -202.0f, 0.0f));
			AddGameObject<Sprite>(L"CreditMozi", Vec2(256*0.5, 128*0.5), Vec3(570.0f, -370.0f, 0.0f));//タイトル用のスプライト生成
			m_Credit = AddGameObject<Sprite>(L"Credit", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f), Col4(1.0f, 1.0f, 1.0f, 0.0f),2);//クレジット生成
			m_black = AddGameObject<BlackOut>(false);
			m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
		}
		catch (...) {
			throw;
		}

		auto BGM = App::GetApp()->GetXAudio2Manager();
		m_BGM = BGM->Start(L"TIlteStage", 0, 0.9f);

	}

	void TilteStage::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);

	}

	void TilteStage::OnUpdate()
	{
		auto keyState = App::GetApp()->GetInputDevice().GetKeyState();//キーボードデバック用

		auto time = App::GetApp()->GetElapsedTime();

		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		auto m_controler = inputDevice.GetControlerVec()[0];

		if (m_count == 0 && m_time >= 0)
		{
			m_water = AddGameObject<Sprite>(L"water0", Vec2(510, 460 * 0.5), Vec3(257.0f, 125.0f, 0.0f));
			m_count++;
		}
		if (m_count == 1 && m_time >= 0.2)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water", Vec2(510, 460 * 0.5), Vec3(257.0f, 140.0f, 0.0f));
			m_count++;
		}
		if (m_count == 2 && m_time >= 0.4)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water2", Vec2(510, 460 * 0.6), Vec3(257.0f, 178.0f, 0.0f));
			m_count++;
		}
		if (m_count == 3 && m_time >= 0.6)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water3", Vec2(510, 510 * 0.6), Vec3(257.0f, 190.0f, 0.0f));
			m_count++;
		}
		if (m_count == 4 && m_time >= 0.8f)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water3", Vec2(510, 510 * 0.8), Vec3(257.0f, 230.0f, 0.0f));
			m_count++;
		}
		if (m_count == 5 && m_time >= 1.0f)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water3", Vec2(510, 510 * 0.6), Vec3(257.0f, 190.0f, 0.0f));
			m_count++;
		}
		if (m_count == 6 && m_time >= 1.15f)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water2", Vec2(510, 460 * 0.6), Vec3(257.0f, 178.0f, 0.0f));
			m_count++;
		}
		if (m_count == 7 && m_time >= 1.25f)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water", Vec2(510, 460 * 0.5), Vec3(257.0f, 140.0f, 0.0f));
			m_count++;
		}
		if (m_count == 8 && m_time >= 1.3f)
		{
			RemoveGameObject<Sprite>(m_water);
			m_water = AddGameObject<Sprite>(L"water0", Vec2(510, 460 * 0.5), Vec3(257.0f, 130.0f, 0.0f));
			m_count = 1;
			m_time = 0;
		}

		m_time += time;

		if (m_transparency > 0.0f && !m_transparent)
		{
			m_transparency -= 1.0f * App::GetApp()->GetElapsedTime();
		}
		if (m_transparency < 1 && m_transparent)
		{
			m_transparency += 1.0f * App::GetApp()->GetElapsedTime();
		}

		if (m_transparency <= 0)
		{
			m_transparent = true;
		}
		if (m_transparency >= 1)
		{
			m_transparent = false;
		}

		m_spriteMozi->SetColor(Col4(0.3, 0.3, 0.3, m_transparency));
		m_spriteB->SetColor(Col4(1, 0, 0, m_transparency));

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B && m_creditCount)
		{
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			auto SE = SEManager->Start(L"Decision", 0, 0.9f);
			
			m_black->SetSwitch(true);//暗転開始

		}
		if (m_black->GetBlackOutFlag())
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");//ゲームシーンに移動する
		}

		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_X&&!m_black->GetSwitch())
		{
			if (m_creditCount)
			{
				m_creditCount = false;
				m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (!m_creditCount)
			{
				m_creditCount = true;
				m_Credit->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}

}
//end basecross
