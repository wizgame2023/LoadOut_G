/*!
@file UIManager.cpp
@brief UIのマネージャー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIManager::UIManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr),
		m_keyGetFlag(false),
		m_text(nullptr),
		m_sprite(nullptr),
		m_spriteNum(0)
	{

	}

	UIManager::~UIManager()
	{

	}

	//作成
	void UIManager::OnCreate()
	{
		auto stage = GetStage();
		m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		int enemyUpCount = m_stageManager->GetUpEnemyCount();//敵を打ち上げた敵の数取得
		int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//敵を打ち上げるべき敵の数取得
		int StageMode = m_stageManager->GetStageMode();//ステージルール取得

		//特定の敵を倒して鍵を入手するモード処理
		if (StageMode == 1)
		{
			m_text = GetStage()->AddGameObject<Sprite>(L"EnemyUpText2", Vec2(180.0f, 100.0f), Vec3(-540.0f, 100.0f, 0.0f));//敵を倒した数(テキスト)
		}
		//複数敵を倒して鍵を入手するモード処理
		if (StageMode == 2)
		{
			m_text = GetStage()->AddGameObject<Sprite>(L"EnemyUpText", Vec2(120.0f*1.2f, 60.0f*1.2f), Vec3(-560.0f, 100.0f, 0.0f));//敵を倒した数(テキスト)
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Slash", Vec2(20.0f, 20.0f), Vec3(-635.0f+176.0f, 100.0f, 0.0f));//スラッシュ
			m_spriteNum = stage->AddGameObject<NuberManager>(enemyUpCount, Vec2(20.0f, 20.0f), Vec3(-635.0f + 160.0f, 400 - 300.0f, 0.0f), false);//敵を打ち上げた合計数
			m_spriteNumSecond = stage->AddGameObject<NuberManager>(enemyUpCountMax, Vec2(20.0f, 20.0f), Vec3(-635.0f + 190.0f, 400 - 300.0f, 0.0f), false);//敵を打ち上げる目標数
		}
	}

	//更新
	void UIManager::OnUpdate()
	{
		auto stage = GetStage();
		int StageMode = m_stageManager->GetStageMode();//ステージルール取得
		//特定の敵を倒して鍵を入手するモード処理
		if (StageMode == 1 && !m_keyGetFlag)
		{

		}
		//複数敵を倒して鍵を入手するモード処理
		if (StageMode == 2 && !m_keyGetFlag)
		{		
			int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//敵を飛ばす目標数を取得
			int enemyUpCount = m_stageManager->GetUpEnemyCount();
			m_spriteNum->SetNum(enemyUpCount);

			//敵を目標数飛ばしたら敵を倒した数をカウントを終わらせてチェックのテクスチャを出す
			if (enemyUpCount >= enemyUpCountMax)
			{
				stage->RemoveGameObject<Sprite>(m_sprite);//スラッシュ削除
				m_spriteNum->SetDestroyFlag(true);//削除フラグをオンにする
				m_spriteNumSecond->SetDestroyFlag(true);//削除フラグをオンにする				
				
				GetStage()->AddGameObject<Sprite>(L"Check", Vec2(50.0f, 50.0f), Vec3(-640.0f + 172.0f, 400 - 295.0f, 0.0f));//チェックマーク生成
				m_keyGetFlag = true;//鍵を手に入れていることを伝える
			}
		}
	}

	void UIManager::BatteryHow()
	{
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		
	}

}
//end basecross
