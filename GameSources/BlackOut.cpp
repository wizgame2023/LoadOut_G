/*!
@file BlackOut.cpp
@brief �Ó]
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	BlackOut::BlackOut(shared_ptr<Stage>& stagePtr, bool blackorLight) :
		GameObject(stagePtr),
		m_switch(false),
		m_blackorLight(blackorLight),
		m_unBlackOutFlag(false),
		m_blackOutFlag(false)
	{

	}

	BlackOut::~BlackOut()
	{

	}

	void BlackOut::OnCreate()
	{
		//�Ó]����ۂ̏����X�v���C�g
		if (!m_blackorLight)
		{
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0), Vec3(0), Col4(1.0f, 1.0f, 1.0f, 0.0f));
			m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 0.0f));//�F�����
		}
		//���]����ۂ̏����X�v���C�g
		if (m_blackorLight)
		{
			m_sprite = GetStage()->AddGameObject<Sprite>(L"Black", Vec2(1280, 800), Vec3(0), Vec3(0), Col4(1.0f, 1.0f, 1.0f, 1.0f));
			m_sprite->SetColor(Col4(1.0f, 1.0f, 1.0f, 1.0f));//�F�����
		}

	}

	void BlackOut::OnUpdate()
	{
		float delta = App::GetApp()->GetElapsedTime();
		Col4 spriteColor = m_sprite->GetColor();

		//�Ó]�����J�n����Ȃ�ʂ�
		if (m_switch)
		{
			//�Ó]����
			if (!m_blackorLight)
			{
				spriteColor.w += delta;
				m_sprite->SetColor(spriteColor);//�F�����
			}
			//���]����
			if (m_blackorLight)
			{
				spriteColor.w -= delta;
				m_sprite->SetColor(spriteColor);//�F�����
			}
		}

		//�Ó]����F�Ŗ��ߐs�����ꂽ��Ó]�I���̃t���O
		if (spriteColor.w >= 1.0f)
		{
			m_blackOutFlag = true;
		}
		else
		{
			m_blackOutFlag = false;
		}

		//���]����F�Ŗ��ߐs�����ꂽ��Ó]�I���̃t���O
		if (spriteColor.w <= 0.0f)
		{
			m_unBlackOutFlag = true;
		}
		else
		{
			m_unBlackOutFlag = false;
		}
	}

	//�����������Ȃ����̃Z�b�^�[
	void BlackOut::SetSwitch(bool OnOff)
	{
		m_switch = OnOff;
	}

	//�Ó]�I��������̃Q�b�^
	bool BlackOut::GetBlackOutFlag()
	{
		return m_blackOutFlag;
	}
	//���ÏI��������̃Q�b�^
	bool BlackOut::GetUnBlackOutFlag()
	{
		return m_unBlackOutFlag;
	}

	

}
//end basecross
