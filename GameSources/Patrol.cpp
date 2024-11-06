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
		
		m_time += app()->GetElapsedTime();

		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));
		auto right = m_right * sin(rad);
		auto forward = m_forward * cos(rad);
		if (!m_destinationDecision)
		{

			if (!m_wallCheck)
			{

				if (m_numbers == 0)
				{
					m_destinationPos.x += m_point;
					m_destinationDecision = true;
				}
				else if (m_numbers == 1)
				{
					m_destinationPos.z += m_point;
					m_destinationDecision = true;

				}
				else if (m_numbers == 2)
				{
					m_destinationPos.x -= m_point;
					m_destinationDecision = true;

				}
				else if(m_numbers == 3 )
				{
					m_destinationPos.z -= m_point;
					m_destinationDecision = true;
				}

				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
			if (m_wallCheck)
			{
				if (m_rightCheck)
				{
					m_destinationPos.x= 0;
					m_destinationPos.z -= m_point;
					m_wallCheck = false;
					m_destinationDecision = true;
					m_forwardCheck = false;
				}
				else if (m_forwardCheck)
				{
					m_destinationPos.z = 0;
					m_destinationPos.x -= m_point;
					m_wallCheck = false;
					m_destinationDecision = true;
					m_forwardCheck = false;

				}
			}

		}
		else if (m_destinationDecision)
		{
			m_ownerRot.y = rad;
			if (m_numbers%2==0  && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_moveTime +=app()->GetElapsedTime();
				m_rightCheck = true;
			}
			else if (m_numbers % 2 == 1 <= m_point && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_moveTime += app()->GetElapsedTime();
				m_forwardCheck=true;
			}
			if (m_moveTime > 5)
			{
				m_numbers++;
				m_time = 0;
				m_moveTime = 0;
				m_destinationDecision = false;

				if ( m_rightCheck)
				{
					m_wallCheck = true;
					m_destinationDecision = false;
				}
				else if (m_forwardCheck)
				{
					m_wallCheck = true;
					m_destinationDecision = false;

				}
			}
		}

		m_trans->SetRotation(m_ownerRot);
		m_trans->SetPosition(m_ownerPos);

		float deg = rad * 180 / XM_PI;

		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"�ړI�n_x : " << m_destinationPos.x
			<< L"\n�ړI�n_z : " << m_destinationPos.z 
			<<L"\n�G�̉�].y : "<<m_ownerRot.y 
			<<L"\n�G�̉�]�ideg�j"<<deg
			<<L"\n�G��Pos.x : "<<m_ownerPos.x 
			<<L"\n�G��Pos.z : "<< m_ownerPos.z
			<<L"\n�ړ����� : "<<m_distance
			<<L"\n�ړ��N�[���^�C�� : "<<m_moveTime
			<<L"\n����X : "<< m_numbers
			<<L"\n�� : "<<m_wallCheck << endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
