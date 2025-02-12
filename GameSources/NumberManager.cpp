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
		m_pos(pos),
		m_destroyFlag(false),
		m_layer(1)
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
	NuberManager::NuberManager(shared_ptr<Stage>& stage, int number, Vec2 scale, Vec3 pos,bool numLenght,float between,int layer) :
		GameObject(stage),
		m_number(number),
		m_scale(scale),
		m_pos(pos),
		m_numLength(numLenght),
		m_between(between),
		m_layer(layer)
	{
	}
	NuberManager::~NuberManager()
	{
	}

	void NuberManager::OnCreate()
	{
		//フラグによって２桁か１桁か決める
		if (!m_numLength)
		{
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number, m_pos);
			m_spriteOne->SetDrawLayer(m_layer);//レイヤー順番を決める
		}
		if (m_numLength)
		{
			m_spriteTen = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale , m_number / 10, Vec3(m_pos.x - m_between, m_pos.y, m_pos.z));
			m_spriteTen->SetDrawLayer(m_layer);//レイヤー順番を決める
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number % 10, Vec3(m_pos.x + m_between, m_pos.y, m_pos.z));
			m_spriteOne->SetDrawLayer(m_layer);//レイヤー順番を決める
		}
	}
	void NuberManager::OnUpdate()
	{		
		auto stage = GetStage();

		if (!m_numLength)
		{
			m_spriteOne->SetNum(m_number);
		}
		if (m_numLength)
		{
			m_spriteTen->SetNum(m_number / 10);		
			m_spriteOne->SetNum(m_number % 10);
		}

		//削除フラグがオンになったら
		if (m_destroyFlag)
		{
			stage->RemoveGameObject<NuberManager>(GetThis<NuberManager>());//自分を消去
			//生成したスプライトを削除
			if (!m_numLength)
			{
				stage->RemoveGameObject<SpriteNum>(m_spriteOne);
			}
			if (m_numLength)
			{
				stage->RemoveGameObject<SpriteNum>(m_spriteOne);
				stage->RemoveGameObject<SpriteNum>(m_spriteTen);
			}

		}

	}

	//消去時処理
	void NuberManager::OnDestroy()
	{

	}

	void NuberManager::SetDestroyFlag(bool OnOff)
	{
		m_destroyFlag = OnOff;
	}

	void NuberManager::SetNum(int number)
	{
		m_number = number;
	}
}
//end basecross
