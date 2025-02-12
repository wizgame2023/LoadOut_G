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
		m_EnemyUpClearNum(enemyUpClearNum),
		m_step(GAMESTART_Start)
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

		auto stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		stageManager->SetUpdateFlag(false);//更新できないようにする

		//auto m_StageText = stage->AddGameObject<Sprite>(L"StageText", Vec2(800/2, 150/2), Vec3(-105.0f, 250.0f, 0.0f));//タイトル用のスプライト生成
		//m_StageText->SetDrawLayer(2);
		auto m_NumberSprite = stage->AddGameObject<NuberManager>(1, Vec2(150/2, 150/2), Vec3(-55.0f, 150.0f, 0.0f), true, 35.0f,2);//現在のステージ数出現

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
		auto stage = GetStage();
		bool removeFlag = false;
		auto delta = App::GetApp()->GetElapsedTime();

		//Bボタンを押したらカウントダウンをする
		if (m_controler.wPressedButtons & XINPUT_GAMEPAD_B && m_step == GAMESTART_Start)
		{
			//生成したスプライトを削除する処理
			for (auto sprite : m_spriteVec)
			{
				auto castSprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castSprite)
				{
					stage->RemoveGameObject<Sprite>(castSprite);
				}
			}
			//ステージモードが複数の敵を倒すモードなら
			if (m_stageMode == 2)
			{
				m_nuberManager->SetDestroyFlag(true);//ナンバーマネージャを削除するフラグを立てる
			}

			m_spriteVec.clear();//スプライト配列のリセット

			m_step = GAMESTART_CountDown_One;//ステップ更新

			//カウントダウンSE再生
			auto SEManager = App::GetApp()->GetXAudio2Manager();
			SEManager->Start(L"CountDownSE", 0, 3.5f);

		}

		//カウントダウン
		if (m_step == GAMESTART_CountDown_One)
		{			
			m_CountDownTimeCount += delta;
			//出てくる時間に少しラグを付けて3を出す
			if (m_CountDownTimeCount > 0.1f)
			{
				m_spriteCountDown = stage->AddGameObject<Sprite>(L"3Tex", Vec2(500, 500));
				m_spriteVec.push_back(m_spriteCountDown);
				m_step = GAMESTART_CountDown_Two;//ステップ更新
			}
		}

		if (m_step == GAMESTART_CountDown_Two)
		{
			m_CountDownTimeCount += delta;
			//2を出す
			if (m_CountDownTimeCount > 1.0f)
			{
				m_spriteCountDown->SetTexture(L"2Tex");
				m_step = GAMESTART_CountDown_Three;//ステップ更新
			}
		}

		if (m_step == GAMESTART_CountDown_Three)
		{
			m_CountDownTimeCount += delta;
			//1を出す
			if (m_CountDownTimeCount > 2.0f)
			{
				m_spriteCountDown->SetTexture(L"1Tex");
				m_step = GAMESTART_CountDown_Start;//ステップ更新

			}
		}

		if (m_step == GAMESTART_CountDown_Start)
		{
			m_CountDownTimeCount += delta;
			//Startを出す
			if (m_CountDownTimeCount > 3.0f)
			{
				m_spriteCountDown->SetTexture(L"Clear");//透明スプライトに置き換え
				m_spriteCountDown = stage->AddGameObject<Sprite>(L"StartTex", Vec2(1000, 1000));
				m_spriteVec.push_back(m_spriteCountDown);

				m_step = GAMESTART_End;//ステップ更新
			}
		}

		if (m_step == GAMESTART_End)
		{
			m_CountDownTimeCount += delta;
			//ある程度Startのテクスチャを見せたら
			if (m_CountDownTimeCount > 3.5f)
			{
				removeFlag = true;//削除を開始する
			}
		}

		//カウントダウンが終わったら消去処理をする
		if (removeFlag)
		{
			stage->RemoveGameObject<GameStart>(GetThis<GameStart>());
			//生成したスプライトを削除する処理
			for (auto sprite : m_spriteVec)
			{
				auto castSprite = dynamic_pointer_cast<Sprite>(sprite);
				if (castSprite)
				{
					stage->RemoveGameObject<Sprite>(castSprite);
				}
			}

			auto objVec = stage->GetGameObjectVec();
			for (auto obj : objVec)
			{
				auto spriteCast = dynamic_pointer_cast<Sprite>(obj);

				if (spriteCast)
				{
					spriteCast->OnClear(false);//透明から戻す
				}
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
		auto stageManager = GetStage()->GetSharedGameObject<StageManager>(L"StageManager");
		stageManager->SetUpdateFlag(true);//更新できるようにする


	}

}
//end basecross
