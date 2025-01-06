/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	NuberManager::NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos) :
		GameObject(stage),
		m_number(number),
		m_scale(scale),
		m_pos(pos)
	{
		if (m_number < 10)
		{
			m_numLength = false;
		}
		if (m_number >= 10)
		{
			m_numLength = true;
		}
	}
	NuberManager::NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos,bool numLenght) :
		GameObject(stage),
		m_number(number),
		m_scale(scale),
		m_pos(pos),
		m_numLength(numLenght)
	{
	}
	NuberManager::~NuberManager()
	{
	}

	void NuberManager::OnCreate()
	{
		if (!m_numLength)
		{
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number, m_pos);
		}
		if (m_numLength)
		{
			m_spriteTen = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale , m_number / 10, Vec3(m_pos.x - 18, m_pos.y, m_pos.z));
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number % 10, Vec3(m_pos.x + 18, m_pos.y, m_pos.z));
		}
	}
	void NuberManager::OnUpdate()
	{		
		if (!m_numLength)
		{
			m_spriteOne->SetNum(m_number);
		}
		if (m_numLength)
		{
			m_spriteTen->SetNum(m_number / 10);		
			m_spriteOne->SetNum(m_number % 10);
		}

	}

	void NuberManager::SetNum(int number)
	{
		m_number = number;
	}
}
//end basecross
