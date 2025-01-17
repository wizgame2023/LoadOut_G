/*!
@file StageManaegr.cpp
@brief ステージの進行を管理する
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(shared_ptr<Stage>& stagePtr,int batteryMax,float repopItemCountTimeMax) :
		GameObject(stagePtr),
		m_repopItemFlag(false),
		m_batteryCountMax(batteryMax),
		m_repopItemCountTimeMax(repopItemCountTimeMax)
	{

	}

	StageManager::~StageManager()
	{

	}

	void StageManager::OnCreate()
	{
		auto stage = GetStage();

		//AStar処理をしてくれるクラスを生成
		auto aStar = stage->AddGameObject<AStar>();
		stage->SetSharedGameObject(L"AStar", aStar);

		//BGM再生
		m_BGMChase = 2;
		m_bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);
		auto a = 0;
	}

	void StageManager::OnUpdate()
	{
		EnemyStateCheck();//敵が追いかけてきてるか確認する
		auto stage = GetStage();
		auto objVec = stage->GetGameObjectVec();
		auto delta = App::GetApp()->GetElapsedTime();

		BGMChange();//BGMを変更する処理
		KeyEvent();//鍵関連のイベント
		RepopItem();//アイテムのリポップ処理
		RepopEnemy();//敵のリポップ処理
		RepopRandamItem();//ランダムアイテムのリポップ処理
		
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

	}

	//BGMを変更する処理
	void StageManager::BGMChange()
	{
		//追いかけられているなら追いかけられているBGM
		if (m_BGMChase && m_BGMhow != 1)
		{
			m_BGMhow = 1;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"Tracking", XAUDIO2_LOOP_INFINITE, 0.9f);
			auto test = 0;
		}
		//追いかけられていなければ普通のBGM
		if (!m_BGMChase && m_BGMhow != 2)
		{
			m_BGMhow = 2;
			m_bgmManager->Stop(m_BGM);
			//BGM
			m_bgmManager = App::GetApp()->GetXAudio2Manager();
			m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);

		}
	}

	//追いかけてくる敵がいるか確認する関数
	void StageManager::EnemyStateCheck()
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

	//Enemyのリポップ装置
	void StageManager::RepopEnemy()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		auto repopSize = m_repopEnemyPos.size();
		auto stage = GetStage();

		//生成する物が１以上あったら生成する
		if (repopSize > 0)
		{
			m_repopEnemyCountTime += delta;
			//クールタイム過ぎたら敵がリポップする
			if (m_repopEnemyCountTime >= 10.0f)
			{
				stage->AddGameObject<Enemy>(m_repopEnemyPos[0]);//リポップ
				m_repopEnemyCountTime = 0;//カウントリセット
				m_repopEnemyPos.erase(m_repopEnemyPos.begin());//生成した物は配列から削除する
			}
		}
	}

	//鍵関係のイベント
	void StageManager::KeyEvent()
	{
		auto stage = GetStage();
		auto objVec = stage->GetGameObjectVec();

		//もし、Playerが鍵を入手したら
		if (m_PlayerKeyFlag == 1)
		{
			m_PlayerKeyFlag = 2;//一度しかこの処理をしないようにする

			//取得したオブジェクトが変換できたら配列に入れる
			for (auto hatch : objVec)
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

	}

	//乾電池のリポップ
	void StageManager::RepopItem()
	{
		auto stage = GetStage();
		auto objVec = stage->GetGameObjectVec();
		auto delta = App::GetApp()->GetElapsedTime();
		auto mapManager = stage->GetSharedGameObject<MapManager>(L"MapManager");

		auto player = stage->GetSharedGameObject<Player>(L"Player");
		int playerBatteryNum = player->GetBatteryCount();//プレイヤーが持っている電池の数

		int countItem = 0;
		//int batteryCountMax = 5;//ステージにあるアイテムの上限 メンバ変数にする

		//取得したオブジェクトが変換できたら配列に入れる
		if (!m_repopItemFlag)//リポップする条件を満たしいない限り見る
		{
			for (auto item : objVec)
			{
				//ハッチの上に柱上のエフェクトを表示させる
				auto castItem = dynamic_pointer_cast<Battery>(item);
				if (castItem)//ハッチ型にキャストする
				{
					countItem++;
				}
			}
			//ステージ上に一定数のアイテム数より下回っているならフラグをオンにする			
			if (countItem+playerBatteryNum < m_batteryCountMax)
			{
				m_repopItemFlag = true;
			}
		}

		//ステージ上に一定数のアイテム数より下回っているならアイテムがポップする
		if (m_repopItemFlag)
		{
			m_repopItemCountTime += delta;//時間経過
			//float m_repopItemCountTimeMax = 5.0f;//リポップする時間

			//クールタイム過ぎたら生成する,クールタイムの時間は調整必須
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
					stage->AddGameObject<Battery>(Vec3(popSelVec), Vec3(0.0f, 0.0f, 0.0f));//生成
					m_repopItemFlag = false;//フラグリセット
				}

			}
		}

	}

	void StageManager::RepopRandamItem()
	{
		auto delta = App::GetApp()->GetElapsedTime();
		auto repopSize = m_repopRandomItemPos.size();
		auto stage = GetStage();

		//生成する物が１以上あったら生成する
		if (repopSize > 0)
		{
			m_repopRamdomItemCountTime += delta;
			//クールタイム過ぎたら敵がリポップする
			if (m_repopRamdomItemCountTime >= 3.0f)
			{
				stage->AddGameObject<RandomItem>(m_repopRandomItemPos[0]);//リポップ
				m_repopRamdomItemCountTime = 0;//カウントリセット
				m_repopRandomItemPos.erase(m_repopRandomItemPos.begin());//生成した物は配列から削除する
			}
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
	//repopEnemyPosのセッター
	void StageManager::SetRepopEnemyPos(Vec3 pos)
	{
		m_repopEnemyPos.push_back(pos);
	}
	//repopRandomItemPosのセッター
	void StageManager::SetRepopRandomItemPos(Vec3 pos)
	{
		m_repopRandomItemPos.push_back(pos);
	}

}
//end basecross
