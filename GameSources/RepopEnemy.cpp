/*!
@file RepopEnemy.cpp
@brief ���������ۂ̓G�̏���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RepopEnemy::RepopEnemy(const shared_ptr<Enemy> ptrOwner,float goalPosY) :
		StateBase(ptrOwner),
		m_goalPosY(goalPosY),
		m_speed(20.0f)
	{

	}

	RepopEnemy::~RepopEnemy()
	{

	}

	void RepopEnemy::OnStart()
	{
		auto ownerTrans = m_Owner->GetComponent<Transform>();
		auto ownerPos = ownerTrans->GetPosition();
		auto ownerQt = ownerTrans->GetQuaternion();
		float delta = App::GetApp()->GetElapsedTime();

		m_Owner->MoveSwitch(false);//�����Ȃ��悤�ɂ���

		//�n�ʂɒ����܂ŗ�������
		if (ownerPos.y > m_goalPosY)
		{
			ownerPos.y -= m_speed * delta;
			ownerQt = ownerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));		

			//Y���W���ڕW�n�_��艺�ɍs������ʒu��ڕW�n�_�ɒ���
			if (ownerPos.y < m_goalPosY)
			{
				ownerPos.y = m_goalPosY;
				m_Owner->ChangeState<Patrol>();//�p�g���[����Ԃɂ���
				m_Owner->MoveSwitch(true);//������悤�ɂ���
			}
		}
			
		ownerTrans->SetQuaternion(ownerQt);
		ownerTrans->SetPosition(ownerPos);//�|�W�V�����Z�b�g
	}

	void RepopEnemy::OnUpdate()
	{
		auto ownerTrans = m_Owner->GetComponent<Transform>();
		auto ownerPos = ownerTrans->GetPosition();
		auto ownerQt = ownerTrans->GetQuaternion();
		float delta = App::GetApp()->GetElapsedTime();

		//�n�ʂɒ����܂ŗ�������
		if (ownerPos.y > m_goalPosY)
		{
			ownerPos.y -= m_speed * delta;
			ownerQt = ownerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			//Y���W���ڕW�n�_��艺�ɍs������ʒu��ڕW�n�_�ɒ���
			if (ownerPos.y < m_goalPosY)
			{
				ownerPos.y = m_goalPosY;
				m_Owner->ChangeState<Patrol>();//�p�g���[����Ԃɂ���
				m_Owner->MoveSwitch(true);//������悤�ɂ���
			}
		}

		ownerTrans->SetQuaternion(ownerQt);
		ownerTrans->SetPosition(ownerPos);//�|�W�V�����Z�b�g

	}

	void RepopEnemy::OnExit()
	{

	}


}
//end basecross
