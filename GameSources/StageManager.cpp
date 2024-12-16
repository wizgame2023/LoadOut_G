/*!
@file StageManaegr.cpp
@brief ステージの進行を管理する
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr),
		m_repopItemFlag(false)
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
		auto mapManager = stage->GetSharedGameObject<MapManager>(L"MapManager");
		auto delta = App::GetApp()->GetElapsedTime();

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

		int countItem = 0;	
		int itemCountMax = 5;//ステージにあるアイテムの上限 メンバ変数にする

		//取得したオブジェクトが変換できたら配列に入れる
		if (!m_repopItemFlag)//リポップする条件を満たしいない限り見る
		{
			for (auto item : obj)
			{
				//ハッチの上に柱上のエフェクトを表示させる
				auto castItem = dynamic_pointer_cast<Item>(item);
				if (castItem)//ハッチ型にキャストする
				{
					countItem++;
				}
			}
			//ステージ上に一定数のアイテム数より下回っているならフラグをオンにする			
			if (countItem < itemCountMax)
			{
				m_repopItemFlag = true;
			}
		}

		//ステージ上に一定数のアイテム数より下回っているならアイテムがポップする
		if (m_repopItemFlag)
		{
			m_repopItemCountTime += delta;//時間経過
			auto m_repopItemCountTimeMax = 5.0f;//リポップする時間

			//クールタイム過ぎたら生成する
			if (m_repopItemCountTime >= m_repopItemCountTimeMax)
			{
				m_repopItemCountTime = 0.0f;//クールタイムリセット

				auto mapSize = stage->GetSharedGameObject<MapManager>(L"MapManager")->GetMapSize();
				mapSize = mapSize;
				float halfMapSize = mapSize / 2;
				
				//ランダムに出現する場所を決める
				auto randX = (rand() % (int)mapSize) - halfMapSize;
				auto randY = halfMapSize - (rand() % (int)mapSize);
				Vec3 randVec = Vec3(randX, 0.0f, randY);
				
				//ランダムに決めた場所がアイテムがない場所なら出現させる
				if (mapManager->SelMapNow(randVec) == mapManager->Map_None)
				{
					auto randSelVec = mapManager->ConvertSelMap(randVec);//セルマップに変える
					auto popSelVec = mapManager->ConvertWorldMap(randSelVec);//ワールド座標に変換する
					stage->AddGameObject<Item>(Vec3(popSelVec),Vec3(0.0f,0.0f,0.0f));//生成
					m_repopItemFlag = false;//フラグリセット
				}

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
