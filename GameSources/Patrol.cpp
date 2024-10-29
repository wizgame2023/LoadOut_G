/*!
@file Patrol.cpp
@brief ����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//����X�e�[�g�̍ŏ��̏���
	void Patrol::OnStart()
	{
	//���L��(Enemy)�����̏�����
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_rot = m_trans->GetRotation();//���L��(Enemy)�̉�]�̎擾
		m_rnd = 1;//�f�o�b�N�p 
		//rnd���P�������ꍇ�A���L��(Enemy)������������
		if (m_rnd ==1)
		{
			m_rot.y = XM_PI;
		}
		//rnd���P�ȊO�������ꍇ�A���L��(Enemy)�������E����
		else if(m_rnd==2)
		{
			m_rot.y = XM_PI*0.5f;
		}
		m_trans->SetRotation(m_rot);
	}

//����X�e�[�g�̍X�V����
	void Patrol::OnUpdate()
	{
	//���L��(Enemy)�����̈ړ�����
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_time += app()->GetElapsedTime();
		m_pos = m_trans->GetPosition();

		Vec3 forward(0, 0, 1);
		Vec3 fod = forward * m_rot.y;
		//rnd��1�������ꍇ�A���L��(Enemy)������������œ���
		if (m_rnd==1)
		{
			if (m_time <= 3)
			{

			}
			//m_point�܂őO�i����
			if (m_distance <= m_point && m_time > 3)
			{
				m_pos +=  m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance++;
			}
			else if (m_distance > m_point)
			{
				m_rot.y += XM_PI * 0.5f;
				m_distance = 0;
				m_time = 0;
			}
		}
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);
	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
