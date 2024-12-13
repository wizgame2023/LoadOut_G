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
			m_spriteMozi = AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -150.0f, 0.0f));
			m_spriteB = AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.5f, 150 * 0.5f), Vec3(0.0f, -150.0f, 0.0f));
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
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーのアナログスティックの向き
		auto m_controler = inputDevice.GetControlerVec()[0];

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
		if (m_controler.wButtons & XINPUT_GAMEPAD_B)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameStage");//ゲームシーンに移動する
		}
	}

}
//end basecross
