/*!
@file GameStart.cpp
@brief ステージを開始するための処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	GameStart::GameStart(shared_ptr<Stage>& ptrStage,int mode,int enemyUpClearNum) :
		GameObject(ptrStage),
		m_stageMode(mode),
		m_EnemyUpClearNum(enemyUpClearNum)
	{

	}

	GameStart::~GameStart()
	{

	}

	//開始時処理
	void GameStart::OnCreate()
	{
		auto stage = GetStage();

		//オブジェクト停止処理
		auto objVec = stage->GetGameObjectVec();
		//アクターを継承しているものだけ取得
		for (auto obj : objVec)
		{
			auto actorCast = dynamic_pointer_cast<Actor>(obj);
			auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

			//アクターを継承しているオブジェクト停止
			if (actorCast)
			{
				actorCast->MoveSwitch(false);//動けないようにする
				m_actorVec.push_back(actorCast);
			}
			if (spriteCast)
			{
				spriteCast->OnClear(true);//透明にする
			}
		}

		//特定の敵を打ち上げると鍵を入手できるモード
		if (m_stageMode == 1)
		{
			m_sprite = stage->AddGameObject<Sprite>(L"ClearConditionsText1",Vec2(1280,800));
			m_spriteVec.push_back(m_sprite);
			auto sprite2 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			m_spriteVec.push_back(sprite2);
			auto sprite3 = stage->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -302.0f, 0.0f));
			sprite3->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			m_spriteVec.push_back(sprite3);
		}
		//敵を一定数打ち上げると鍵を入手できるモード
		if (m_stageMode == 2)
		{
			auto sprite = stage->AddGameObject<Sprite>(L"ClearConditionsText2", Vec2(1280, 800));
			m_spriteVec.push_back(sprite);
			auto sprite2 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			m_spriteVec.push_back(sprite2);
			auto sprite3 = stage->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -302.0f, 0.0f));
			sprite3->SetColor(Col4(1.0f, 0.0f, 0.0f, 1.0f));
			m_spriteVec.push_back(sprite3);		
			//倒すべき敵の数表示
			m_nuberManager = GetStage()->AddGameObject<NuberManager>(m_EnemyUpClearNum, Vec2(150, 150), Vec3(-490.0f, 0.0f, 0.0f), true,80.0f);//個数
			//auto sprite4 = stage->AddGameObject<Sprite>(L"StartMozi", Vec2(900 * 0.6f, 150 * 1.0f), Vec3(0.0f, -300.0f, 0.0f));
			//sprite2->SetColor(Col4(0.3f, 0.3f, 0.3f, 1.0f));
			//m_spriteVec.push_back(sprite4);

		}
	}

	//更新処理
	void GameStart::OnUpdate()
	{
		// インプットデバイスオブジェクト
		auto inputDevice = App::GetApp()->GetInputDevice(); // 様々な入力デバイスを管理しているオブジェクトを取得
		//コントローラーの取得
		auto m_controler = inputDevice.GetControlerVec()[0];
		auto Stage = GetStage();

		//Bボタンを押したらゲームスタート
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B)
		{
			Stage->RemoveGameObject<GameStart>(GetThis<GameStart>());
			//生成したスプライトを削除する処理
			for (auto sprite : m_spriteVec)
			{
				auto test = dynamic_pointer_cast<Sprite>(sprite);
				Stage->RemoveGameObject<Sprite>(test);
			}

			auto objVec = Stage->GetGameObjectVec();
			for (auto obj : objVec)
			{
				auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

				if (spriteCast)
				{
					spriteCast->OnClear(false);//透明から戻す
				}
			}
			//ステージモードが複数の敵を倒すモードなら
			if (m_stageMode == 2)
			{
				m_nuberManager->SetDestroyFlag(true);//ナンバーマネージャを削除するフラグを立てる
			}


		}
	}

	//削除時処理
	void GameStart::OnDestroy()
	{
		//動くオブジェクトが動けるようにする
		for (auto actor : m_actorVec)
		{
			auto actorCheck = actor.lock();
			if (actorCheck)
			{
				actorCheck->MoveSwitch(true);//動ける
			}
		}

	}

}
//end basecross
