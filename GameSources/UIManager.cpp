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
