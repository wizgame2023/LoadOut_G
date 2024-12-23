/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NuberManager::NuberManager(shared_ptr<Stage>& stage, int nuber, Vec2 scale, Vec3 pos) :
		GameObject(stage),
		m_nuber(nuber),
		m_scale(scale),
		m_pos(pos)
	{
	}
	NuberManager::~NuberManager()
	{
	}

	void NuberManager::OnCreate()
	{
		if (m_nuber < 10)
		{
			m_sprite = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_nuber, m_pos);
		}
		else if (m_nuber >= 10)
		{
			m_sprite = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale , m_nuber / 10, Vec3(m_pos.x - 20, m_pos.y, m_pos.z));
			m_sprite = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale , m_nuber % 10, Vec3(m_pos.x+20,m_pos.y,m_pos.z));
		}
	}
	void NuberManager::OnUpdate()
	{

	}
}
//end basecross
