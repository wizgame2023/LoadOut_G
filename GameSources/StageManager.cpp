/*!
@file StageManaegr.cpp
@brief ステージの進行を管理する
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	StageManager::~StageManager()
	{

	}

	void StageManager::OnCreate()
	{
		auto stage = GetStage();

		//BGM再生
		m_BGMChase = 2;
		m_bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);
		auto a = 0;
	}

	void StageManager::OnUpdate()
	{
		BGMChange();
		auto stage = GetStage();
		auto obj = stage->GetGameObjectVec();

		//追いかけられているなら追いかけられているBGM
		if (m_BGMChase&&m_BGMhow !=1)
		{
			m_BGMhow = 1;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"Tracking", XAUDIO2_LOOP_INFINITE, 0.9f);
			auto test = 0;
		}
		//追いかけられていなければ普通のBGM
		if (!m_BGMChase&&m_BGMhow !=2)
		{
			m_BGMhow = 2;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		}

		//ゲームクリアのフラグが立ったら
		if (m_ClearFlag)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameClearStage");//ゲームクリアに移動する
		}
		//ゲームオーバーのフラグが立ったら
		if (m_GameOverFlag)
		{
			PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToGameOverStage");//ゲームオーバーに移動する
		}

		//もし、Playerが鍵を入手したら
		if (m_PlayerKeyFlag == 1)
		{
			m_PlayerKeyFlag = 2;//一度しかこの処理をしないようにする

			//取得したオブジェクトが変換できたら配列に入れる
			for (auto hatch : obj)
			{			
				//ハッチの上に柱上のエフェクトを表示させる
				auto castHatch = dynamic_pointer_cast<Hatch>(hatch);
				if (castHatch)//ハッチ型にキャストする
				{
					auto hatchTrans = castHatch->GetComponent<Transform>();
					auto hatchPos = hatchTrans->GetPosition();

					//筒のエフェクト追加
					GetStage()->AddGameObject<PillarEffect>(hatchPos, L"Escape", Vec2(0.0f, 0.5f), 36);

				}
				auto castPlayer = dynamic_pointer_cast<Player>(hatch);
				if (castPlayer)//プレイヤーにキャスト出来たら
				{
					auto playerTrans = castPlayer->GetComponent<Transform>();
					auto playerPos = playerTrans->GetPosition();

					//鍵の板ポリを表示
				}

			}
		}

		//取得したオブジェクトが変換できたら配列に入れる
		for (auto item : obj)
		{
			//ハッチの上に柱上のエフェクトを表示させる
			auto castItem = dynamic_pointer_cast<Item>(item);
			int countItem = 0;
			if (castItem)//ハッチ型にキャストする
			{
				countItem++;
			}
			//ステージ上に5個未満のアイテム数ならアイテムがポップする
			if (countItem > 5)
			{

			}
		}
	}

	void StageManager::BGMChange()
	{
		auto stage = GetStage();
		auto obj = stage->GetGameObjectVec();
		auto EnemyTracking = 0;
		//取得したオブジェクトがアイテムに変換できたら配列に入れる
		for (auto enemy : obj)
		{
			auto enemycast = dynamic_pointer_cast<Enemy>(enemy);

			if (enemycast)//Enemy型にキャストに成功したら
			{
				auto State = enemycast->GetNowState();//現在のステートを受け取る
				auto trackcast = dynamic_pointer_cast<Tracking>(State);
				if (trackcast)//現在のステートがトラッキング(追いかける処理)の時
				{
					EnemyTracking++;
				}
			}
		}
		m_BGMChase;//追いかける敵がいるか
		if (EnemyTracking > 0)//追いかける敵が一人以上いるなら
		{
			m_BGMChase = true;
		}
		else
		{
			m_BGMChase = false;
		}

		
		
	}

	void StageManager::OnDestroy()
	{
		auto BGM = App::GetApp()->GetXAudio2Manager();
		BGM->Stop(m_BGM);

	}

	//ClearFlagのセッター
	void StageManager::SetClearFlag(bool flag)
	{
		m_ClearFlag = flag;
	}
	//GameOverFlagのセッター
	void StageManager::SetGameOverFlag(bool flag)
	{
		m_GameOverFlag = flag;
	}
	//PlayerKeyFlagのセッター
	void StageManager::SetPlayerKeyFlag(int flag)
	{
		m_PlayerKeyFlag = flag;
	}
}
//end basecross
