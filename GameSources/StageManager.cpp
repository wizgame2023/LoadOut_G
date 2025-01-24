/*!
@file StageManaegr.cpp
@brief ステージの進行を管理する
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	StageManager::StageManager(shared_ptr<Stage>& stagePtr, int batteryMax, float repopItemCountTimeMax,
							   float repopEnemyCountTimeMax, float repopRamdomItemCountTimeMax
								) :
		GameObject(stagePtr),
		m_repopItemFlag(false),
		m_batteryCountMax(batteryMax),
		m_repopItemCountTimeMax(repopItemCountTimeMax),
		m_repopEnemyCountTimeMax(repopEnemyCountTimeMax),
		m_repopRamdomItemCountTimeMax(repopRamdomItemCountTimeMax),
		m_updateFlag(true),
		m_BGMChase(false),
		m_BGMhow(2),
		m_EnemyUpClearNum(0)
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
		m_bgmManager = App::GetApp()->GetXAudio2Manager();
		m_BGM = m_bgmManager->Start(L"StageBGM", XAUDIO2_LOOP_INFINITE, 0.9f);
		m_blackOut = GetStage()->AddGameObject<BlackOut>(false);
		m_pauseButton=GetStage()->AddGameObject<Sprite>(L"PauseButton", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
		auto a = 0;
	}

	void StageManager::OnUpdate()
	{
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

		//フラグがtrueになっているとUpdateできる
		if (!m_updateFlag) return;

		EnemyStateCheck();//敵が追いかけてきてるか確認する
		//auto stage = GetStage();
		//auto objVec = stage->GetGameObjectVec();
		//auto delta = App::GetApp()->GetElapsedTime();

		//決まった数敵を打ち上げたら鍵を入手できる(関数にする)
		if (m_stageMode == 2)
		{
			if (m_upEnemyCount >= m_EnemyUpClearNum)
			{
				m_PlayerKeyFlag = true;//プレイヤーに鍵を持たせるフラグを渡す	
				m_clearManagerCount = 1;//もうクリアマネージャーの処理はしない
			}
		}


		BGMChange();//BGMを変更する処理
		KeyEvent();//鍵関連のイベント
		RepopItem();//アイテムのリポップ処理
		RepopEnemy();//敵のリポップ処理
		RepopRandamItem();//ランダムアイテムのリポップ処理
		PauseEvent();//ポーズ処理
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
			if (m_repopEnemyCountTime >= m_repopEnemyCountTimeMax)
			{
				stage->AddGameObject<Enemy>(m_repopEnemyPos[0]+Vec3(0.0f,30.0f,0.0f), false);//リポップ
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
		auto delta = App::GetApp()->GetElapsedTime();

		//もし、Playerが鍵を入手するフラグが立ったら
		if (m_PlayerKeyFlag == 1)
		{
			GetStage()->GetSharedGameObject<Player>(L"Player")->SetKey(true);//Playerに鍵を渡す
			m_PlayerKeyFlag = 2;//一度しかこの処理をしないようにする

			//鍵を手に入れたことを知らせるテクスチャ追加
			m_KeyGetText = stage->AddGameObject<SpriteMove>(L"KeyGetText", Vec2(800.0f, 400.0f), Vec3(1000.0f, 0.0f, 0.0f), Vec3(0.0f), Col4(1), -500, 3);

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
		//鍵を手に入れたのを知らせるテキストの移動処理
		if (m_PlayerKeyFlag == 2)
		{
			auto GetTextTrans = m_KeyGetText->GetComponent<Transform>();
			auto GetTextPos = GetTextTrans->GetPosition();
			//GetTextPos.x -= 500 * delta;//移動
			//GetTextTrans->SetPosition(GetTextPos);

		//	//テキストが画面範囲外に移動したら移動処理をしないようにする
		//	if (GetTextPos.x >= 1000)
		//	{
		//		m_PlayerKeyFlag = 3;//この処理をしないようにする
		//		stage->RemoveGameObject<Sprite>(m_KeyGetText);
		//	}
		//}
		}

	}

	//ステージのクリア条件を決める関数
	void StageManager::ClearMode(int mode,int modeTwoCountMax)
	{			
		auto stage = GetStage();
		auto delta = App::GetApp()->GetElapsedTime();
		auto mapManager = stage->GetSharedGameObject<MapManager>(L"MapManager");
		//m_EnemyUpClearNum = modeTwoCountMax;//たおさないと行けない数を決める

		//敵が鍵を持っているモード
		if (mode == 1&& m_clearManagerCount == 0)
		{
			m_stageMode = mode;
			auto objVec = stage->GetGameObjectVec();
			vector<weak_ptr<Enemy>> enemyVec;
			//ステージからオブジェクトを取得し、その中で取得できた敵の中からランダムに鍵を持たせる
			for (auto obj : objVec)
			{
				auto castEnemy = dynamic_pointer_cast<Enemy>(obj);
				if (castEnemy)//キャスト成功したら
				{
					enemyVec.push_back(castEnemy);//配列に入れる
				}
			}

			//鍵を持つ敵をランダムに決める
			int haveKeyNum = rand() % enemyVec.size();

			//決まった敵に鍵をもつタグを付ける
			enemyVec[haveKeyNum].lock()->AddTag(L"Key");

			m_clearManagerCount = 1;//もうクリアマネージャーの処理はしない
		}
		//敵を複数倒すと鍵を入手できるモード
		if (mode == 2 && m_clearManagerCount == 0)
		{
			m_EnemyUpClearNum = modeTwoCountMax;//たおさないと行けない数を決める
			m_stageMode = mode;
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

		int countItem = 0;//ステージ上の乾電池の数を数える

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
			if (countItem + playerBatteryNum < m_batteryCountMax)
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

	//ランダムアイテムのリポップ処理
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
			if (m_repopRamdomItemCountTime >= m_repopRamdomItemCountTimeMax)
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

	void StageManager::PauseEvent()
	{
		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		//auto& keyState = App::GetApp()->GetInputDevice().GetKeyState();
		auto stage = GetStage();//ステージ取得
		//ステージのオブジェクトを全て取得
		auto objVec = stage->GetGameObjectVec();
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && m_pausCount == 0)
		{
			m_white = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 0.5f), 11);
			PauseScene = GetStage()->AddGameObject<Sprite>(L"PauseScene", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_pauseText= GetStage()->AddGameObject<Sprite>(L"PauseText", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_pauseText2 = GetStage()->AddGameObject<Sprite>(L"PauseText2", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_pauseText3 = GetStage()->AddGameObject<Sprite>(L"PauseText3", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_pauseText4 = GetStage()->AddGameObject<Sprite>(L"PauseText4", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_operation = GetStage()->AddGameObject<Sprite>(L"Operation", Vec2(700, 600), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 0.0f), 12);
			m_decisionMozi = GetStage()->AddGameObject<Sprite>(L"DecisionMozi", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
			m_spriteB = GetStage()->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f),Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f), 11);
			GetStage()->RemoveGameObject<Sprite>(m_pauseButton);

			m_count = 0;
			m_pausCount++;
			m_pause = true;
			m_pauseFlag = true;
			m_stickCheck = true;
			m_operationFlag = false;
		}
		else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_START && m_pausCount == 1)
		{
			m_pausCount--;
			m_pause = false;
			m_pauseFlag = true;
			m_pauseButton = GetStage()->AddGameObject<Sprite>(L"PauseButton", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
		}

		if (m_pausCount == 1)
		{
			switch (m_count)
			{
			case 0:
				m_pauseText->SetColor(Col4(1, 0, 0, 1));
				m_pauseText2->SetColor(Col4(1, 1, 1, 1));
				m_pauseText3->SetColor(Col4(1, 1, 1, 1));
				m_pauseText4->SetColor(Col4(1, 1, 1, 1));
				break;
			case 1:
				m_pauseText->SetColor(Col4(1, 1, 1, 1));
				m_pauseText2->SetColor(Col4(1, 0, 0, 1));
				m_pauseText3->SetColor(Col4(1, 1, 1, 1));
				m_pauseText4->SetColor(Col4(1, 1, 1, 1));
				break;
			case 2:
				m_pauseText->SetColor(Col4(1, 1, 1, 1));
				m_pauseText2->SetColor(Col4(1, 1, 1, 1));
				m_pauseText3->SetColor(Col4(1, 0, 0, 1));
				m_pauseText4->SetColor(Col4(1, 1, 1, 1));
				break;
			case 3:
				m_pauseText->SetColor(Col4(1, 1, 1, 1));
				m_pauseText2->SetColor(Col4(1, 1, 1, 1));
				m_pauseText3->SetColor(Col4(1, 1, 1, 1));
				m_pauseText4->SetColor(Col4(1, 0, 0, 1));
				break;
			}


			if (cntlVec[0].fThumbLY < 0 && !m_stickCheck && m_count < 3)
			{
				m_count++;
				m_stickCheck = true;
			}
			if (cntlVec[0].fThumbLY > 0 && !m_stickCheck && m_count > 0)
			{
				m_count--;
				m_stickCheck = true;
			}
			if (!cntlVec[0].fThumbLY && !m_blackOut->GetSwitch())
			{
				m_stickCheck = false;
			}
			if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B)
			{
				switch (m_count)
				{
				case 0:
					m_pausCount--;
					m_pause = false;
					m_pauseFlag = true;
					m_pauseButton = GetStage()->AddGameObject<Sprite>(L"PauseButton", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
					break;
				case 1:
					m_operationFlag = true;
					break;
				case 2:
					m_stickCheck = true;
					m_blackOut->SetSwitch(true);
					break;
				case 3:
					m_stickCheck = true;
					m_blackOut->SetSwitch(true);
					break;
				}
			}

			if (m_count==1)
			{
				if (m_operationFlag)
				{
					GetStage()->RemoveGameObject<Sprite>(m_spriteB);
					GetStage()->RemoveGameObject<Sprite>(m_decisionMozi);
					m_stickCheck = true;
					m_operation->SetColor(Col4(1, 1, 1, 1));
				}
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A && m_operationFlag)
				{
					m_decisionMozi = GetStage()->AddGameObject<Sprite>(L"DecisionMozi", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 1.0f, 1.0f, 1.0f), 11);
					m_spriteB = GetStage()->AddGameObject<Sprite>(L"StartMoziB", Vec2(900 * 0.3f, 150 * 0.3f), Vec3(570.0f, -370.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Col4(1.0f, 0.0f, 0.0f, 1.0f), 11);
					m_operation->SetColor(Col4(1, 1, 1, 0));
					m_operationFlag = false;
				}
			}
			if (m_blackOut->GetBlackOutFlag() && m_count == 2)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToTilteStage");//ゲームシーンに移動する
			}
			if (m_blackOut->GetBlackOutFlag() && m_count == 3)
			{
				PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), L"ToSelectStage");//ゲームシーンに移動する

			}
		}

		if (m_pause && m_pauseFlag)
		{
			//取得したオブジェクトがアイテムに変換できたら配列に入れる
			for (auto obj : objVec)
			{
				auto castEnemy = dynamic_pointer_cast<Enemy>(obj);
				auto castPlayer = dynamic_pointer_cast<Player>(obj);
				auto castManhole = dynamic_pointer_cast<Manhole>(obj);
				auto castBattery = dynamic_pointer_cast<Battery>(obj);

				if (castEnemy)
				{
					castEnemy->MoveSwitch(false);//うごかなくさせる
				}
				if (castPlayer)
				{
					castPlayer->MoveSwitch(false);//うごかなくさせる
				}
				if (castManhole)
				{
					castManhole->SetUpdateSwitch(false);//うごかなくさせる
				}
				if (castBattery)
				{
					castBattery->SetUpdateSwitch(false);////動くようにする
				}

			}
		}
		if (!m_pause && m_pauseFlag)
		{
			m_pause = false;
			GetStage()->RemoveGameObject<Sprite>(m_white);
			GetStage()->RemoveGameObject<Sprite>(PauseScene);
			GetStage()->RemoveGameObject<Sprite>(m_pauseText);
			GetStage()->RemoveGameObject<Sprite>(m_pauseText2);
			GetStage()->RemoveGameObject<Sprite>(m_pauseText3);
			GetStage()->RemoveGameObject<Sprite>(m_pauseText4);
			GetStage()->RemoveGameObject<Sprite>(m_operation);
			GetStage()->RemoveGameObject<Sprite>(m_decisionMozi);
			GetStage()->RemoveGameObject<Sprite>(m_spriteB);

			for (auto obj : objVec)
			{
				auto castEnemy = dynamic_pointer_cast<Enemy>(obj);
				auto castPlayer = dynamic_pointer_cast<Player>(obj);
				auto castManhole = dynamic_pointer_cast<Manhole>(obj);
				auto castBattery = dynamic_pointer_cast<Battery>(obj);

				if (castEnemy)
				{
					castEnemy->MoveSwitch(true);//動くようにする
				}
				if (castPlayer)
				{
					castPlayer->MoveSwitch(true);//動くようにする
				}
				if (castManhole)
				{
					castManhole->SetUpdateSwitch(true);////動くようにする
				}
				if (castBattery)
				{
					castBattery->SetUpdateSwitch(true);////動くようにする
				}

			}
		}
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
	//アップデートするかのセッター
	void StageManager::SetUpdateFlag(bool flag)
	{
		m_updateFlag = flag;
	}

	void StageManager::AddUpEnemyCount(int count)
	{
		m_upEnemyCount += count;
	}

}
//end basecross
