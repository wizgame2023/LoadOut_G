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

		auto w = 250;
		auto h = 100;
		for (int j = 1; j < 2; j++)
		{

		}
		for (int i = 1; i < m_allStage / 2 + 1; i++)
		{
			if (i <= 5)
			{
				m_sprite = AddGameObject<SpriteNum>(L"Number", Vec2(50, 50), i, Vec3((-500 - w) + (w * i), 250.0f, 0.0f));
			}
			else if (i > 5 && i < 10)
			{
				m_sprite = AddGameObject<SpriteNum>(L"Number", Vec2(50, 50), i, Vec3((-500 - w) + (w * (i - 5)), 250.0f - h, 0.0f));
			}
			else if (i >= 10)
			{
				m_sprite = AddGameObject<SpriteNum>(L"Number", Vec2(50, 50), 1, Vec3((-500 - w) + (w * (i - 5)-12), 250.0f - h, 0.0f));
				m_sprite = AddGameObject<SpriteNum>(L"Number", Vec2(50, 50), 0, Vec3((-500 - w) + (w * (i - 5) + 12), 250.0f - h, 0.0f));

			}
		}
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


		if (m_controler.wButtons & XINPUT_GAMEPAD_B)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//ゲームシーンに移動する
		}
	}

}
//end basecross
