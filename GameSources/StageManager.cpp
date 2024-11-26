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

		//追いかけられているなら追いかけられているBGM
		if (m_BGMChase&&m_BGMhow !=1)
		{
			m_BGMhow = 1;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"TIlteStage", XAUDIO2_LOOP_INFINITE, 0.9f);
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

	}


}
//end basecross
