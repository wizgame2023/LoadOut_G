/*!
@file Character.cpp
@brief �L�����N�^�[�Ȃǎ���
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
		//�t���O�ɂ���ĂQ�����P�������߂�
		if (!m_numLength)
		{
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number, m_pos);
			m_spriteOne->SetDrawLayer(m_layer);//���C���[���Ԃ����߂�
		}
		if (m_numLength)
		{
			m_spriteTen = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale , m_number / 10, Vec3(m_pos.x - m_between, m_pos.y, m_pos.z));
			m_spriteTen->SetDrawLayer(m_layer);//���C���[���Ԃ����߂�
			m_spriteOne = GetStage()->AddGameObject<SpriteNum>(L"Number", m_scale, m_number % 10, Vec3(m_pos.x + m_between, m_pos.y, m_pos.z));
			m_spriteOne->SetDrawLayer(m_layer);//���C���[���Ԃ����߂�
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

		//�폜�t���O���I���ɂȂ�����
		if (m_destroyFlag)
		{
			stage->RemoveGameObject<NuberManager>(GetThis<NuberManager>());//����������
			//���������X�v���C�g���폜
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

	//����������
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
