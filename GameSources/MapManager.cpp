/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MapManager::MapManager(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}
	MapManager::~MapManager()
	{
	}

	void MapManager::OnCreate()
	{

	}

	void MapManager::OnUpdate()
	{

	}

	//ワールド座標をセル座標に変換する
	Vec2 MapManager::MyMapNow(Vec3 worldPosition)
	{
		float length = ((worldPosition.x + 45) / 10.0f) + 0.5f;//横のセル座標
		float height = -((worldPosition.z - 45) / 10.0f) + 0.5f;//縦のセル座標

		return Vec2((int)length, (int)height);

	}

}
//end basecross
