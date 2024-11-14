/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapManager::MiniMapManager(shared_ptr<Stage>& stagePtr) :
		GameObject(stagePtr)
	{

	}

	MiniMapManager::~MiniMapManager()
	{

	}

	void MiniMapManager::OnCreate()
	{
		auto stage = GetStage();//ステージ取得
		float Lenght = 225.0f;//ミニマップの直径
		stage->AddGameObject<Sprite>(L"Gray", Vec2(Lenght, Lenght), Vec3(-640+(Lenght/2.0f)+10.0f, 400.0f - (Lenght / 2.0f)-10.0f, 0.0f));
	}

	void MiniMapManager::OnUpdate()
	{

	}

}
//end basecross
