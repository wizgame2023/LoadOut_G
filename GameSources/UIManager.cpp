/*!
@file UIManager.cpp
@brief UI�̃}�l�[�W���[
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

	//�쐬
	void UIManager::OnCreate()
	{

	}

	//�X�V
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
