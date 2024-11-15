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
		m_miniMapSize(miniMapSize),
		m_mapMagnification(m_miniMapSize / m_mapSize)
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


		m_pos =Vec3((playerPos.x*m_mapMagnification)+m_miniMapStartPos.x,(playerPos.y*m_mapMagnification)+m_miniMapStartPos.y,0.0f);
		//m_pos = 

		trans->SetPosition(m_pos);

		SetDrawLayer(m_miniMapStartPos.z);
	}




}
//end basecross
