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

	}

//����X�e�[�g�̍X�V����
	void Patrol::OnUpdate()
	{
	//���L��(Enemy)�̈ړ�����
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));
		m_ownerRot.y = rad;
		float deg = rad * 180 / XM_PI;

		auto right = m_right * sin(rad);
		auto forward = m_forward * sin(rad);

		if (!m_destinationDecision)
		{
			if (m_rnd==1)
			{
				if (m_ownerPos.x<=m_ownerPos.z)
				{
					m_destinationPos.x += m_point;
					m_destinationDecision = true;
				}
			}
		}
		else if (m_destinationDecision)
		{
			m_time += app()->GetElapsedTime();
			if (m_destinationPos.x > m_destinationPos.z && m_distance <= m_point)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance +=m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			else if (m_destinationPos.x < m_destinationPos.z && m_distance <= m_point)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			if(m_ownerPos==m_destinationPos)
			{
				m_destinationDecision = false;
				m_distance = 0;
			}
		}

		m_trans->SetRotation(m_ownerRot);
		m_trans->SetPosition(m_ownerPos);


		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"�ړI�n_x : " << m_destinationPos.x
			<< L"\n�ړI�n_z : " << m_destinationPos.z 
			<<L"\n�G�̉�].y : "<<m_ownerRot.y 
			<<L"\n�G�̉�]�ideg�j"<<deg
			<<L"\n�G��Pos.x : "<<m_ownerPos.x 
			<<L"\n�G��Pos.z : "<< m_ownerPos.z
			<<L"\n�ړ����� : "<<m_distance << endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
