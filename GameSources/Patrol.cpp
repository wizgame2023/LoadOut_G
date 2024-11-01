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
		m_time += app()->GetElapsedTime();
		auto right = m_right * sin(rad);
		auto forward = m_forward * cos(rad);
		

		if (!m_destinationDecision)
		{
			if (m_rnd==1)
			{
				if (m_ownerPos.x == m_ownerPos.z)
				{
					m_destinationPos.x += m_point;
					m_numbersX++;
					m_destinationDecision = true;
				}
				else if (m_ownerPos.x > m_ownerPos.z)
				{
					m_destinationPos.z += m_point;
					m_destinationDecision = true;
					m_numbersZ++;
				}
			}
		}
		else if (m_destinationDecision)
		{
			auto endTime= app()->GetElapsedTime();
			if (m_destinationPos.x > m_destinationPos.z && m_distance <= m_point && m_time > 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance +=m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			else if (m_destinationPos.x == m_destinationPos.z && m_distance <= m_point && m_time > 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			if (m_distance >= m_point)
			{
				m_distance = 0;
				m_time = 0;

				m_ownerPos.x = m_point * m_numbersX;
				m_ownerPos.z = m_point * m_numbersZ;

				m_destinationDecision = false;
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
			<<L"\n�ړ����� : "<<m_distance
			<<L"\n�ړ��N�[���^�C�� : "<<m_time
			<<L"\n����X : "<< m_numbersX
			<< L"\n����Z : " << m_numbersZ
			<< endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
