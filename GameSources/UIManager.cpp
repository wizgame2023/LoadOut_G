/*!
@file UIManager.cpp
@brief UIのマネージャー
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	UIManager::UIManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	UIManager::~UIManager()
	{

	}

	//作成
	void UIManager::OnCreate()
	{		
		//auto stage = GetStage();
		//m_stageManager = stage->GetSharedGameObject<StageManager>(L"StageManager");
		//int enemyUpCount = m_stageManager->GetUpEnemyCount();//敵を打ち上げた敵の数取得
		//int enemyUpCountMax = m_stageManager->GetUpEnemyCountMax();//敵を打ち上げるべき敵の数取得

		//GetStage()->AddGameObject<Sprite>(L"EnemyUpText", Vec2(120.0f, 60.0f), Vec3(-580.0f, 100.0f, 0.0f));//敵を倒した数(テキスト)
		//GetStage()->AddGameObject<Sprite>(L"Slash", Vec2(20.0f, 20.0f), Vec3(-640.0f+147.0f, 100.0f, 0.0f));//スラッシュ
		//auto m_spriteNum = stage->AddGameObject<NuberManager>(enemyUpCount, Vec2(20.0f, 20.0f), Vec3(-640.0f + 130.0f, 400 - 300.0f, 0.0f), false);//敵を打ち上げる合計数
		//auto m_spriteNum2 = stage->AddGameObject<NuberManager>(enemyUpCountMax, Vec2(20.0f, 20.0f), Vec3(-640.0f + 165.0f, 400 - 300.0f, 0.0f), false);//敵を打ち上げる目標数
	}

	//更新
	void UIManager::OnUpdate()
	{

	}

	void UIManager::BatteryHow()
	{
		auto stage = GetStage();
		auto player = stage->GetSharedGameObject<Player>(L"Player");
		
	}

}
//end basecross
