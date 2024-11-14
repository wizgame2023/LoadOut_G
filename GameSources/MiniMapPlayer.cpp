/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	MiniMapPlayer::MiniMapPlayer(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size,
									Vec3 miniMapStartPos, float mapSize, float miniMapSize,
									Vec3 pos, Vec3 rot, Col4 color) :
		Sprite(stagePtr, textureName, size, pos, rot, color),
		m_miniMapStartPos(miniMapStartPos),
		m_mapSize(mapSize),
		m_miniMapSize(miniMapSize)
	{

	}

	MiniMapPlayer::~MiniMapPlayer()
	{

	}

	void MiniMapPlayer::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();
		
		//Playerのポジションをミニマップの座標に変換する
		auto trans = GetComponent<Transform>();

		playerPos.y = playerPos.z;
		playerPos.z = 5.0f;

		m_pos = m_miniMapStartPos+(playerPos * (m_mapSize / m_miniMapSize));

		trans->SetPosition(m_pos);

	}




}
//end basecross
