/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	
	SpriteMove::SpriteMove(shared_ptr<Stage>& stagePtr, wstring textureName, Vec2 size, Vec3 pos, Vec3 rot, Col4 color, float speed,int layer) :
		Sprite(stagePtr, textureName, size, pos, rot, color, layer),
		m_speed(speed)
	{
	}
	SpriteMove::~SpriteMove()
	{
	}
	void SpriteMove::OnCreate()
	{
		Sprite::OnCreate();
	}
	void SpriteMove::OnUpdate()
	{
		//フラグがオンになったらアップデートする
		if (!m_updateFlag) return;

		float time = App::GetApp()->GetElapsedTime();
		//スプライトの移動
		m_pos.x += m_speed * time;
		m_trans->SetPosition(m_pos);

		//画面から出たら消える処理
		if (m_pos.x >= 1000 || m_pos.x <= -1000)
		{
			GetStage()->RemoveGameObject<SpriteMove>(GetThis<SpriteMove>());
		}
	}
}
//end basecross
