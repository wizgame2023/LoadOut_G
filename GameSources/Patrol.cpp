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
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾

		//Ray�̎擾
		m_forwardRay = m_Owner->GetForwardRay();//���L��(Enemy)�̑O������Ray
		m_playerRay = m_Owner->GetPlayerRay();//���L��(Enemy)����player�̕�����Ray

		m_time += app()->GetElapsedTime();//�f���^�^�C��

		//�x�N�g���̐���
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));//���L��(Enemy)����player�̕����̊p�x
		auto right = m_right * sin(rad);//���s�����̃x�N�g��
		auto forward = m_forward * cos(rad);//���������̃x�N�g��
		m_ownerRot.y = rad;//

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
					m_minus = true;

				}
				else if(m_numbers == 3 )
				{
					m_destinationPos.z -= m_point;
					m_destinationDecision = true;
					m_minus = true;
				}
				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
			if (m_wallCheck)
			{
				if (m_numbers == 0)
				{
					m_destinationPos.x += m_point;
					m_destinationPos.z = m_ownerPos.z;
					m_destinationDecision = true;
					m_wallCheck = false;
				}
				if (m_numbers == 1)
				{
					m_destinationPos.z += m_point;
					m_destinationPos.x = m_ownerPos.x;
					m_destinationDecision = true;
					m_wallCheck = false;
				}
				else if (m_numbers == 2)
				{
					m_destinationPos.x-= m_point;
					m_destinationPos.z = m_ownerPos.z;
					m_destinationDecision = true;
					m_minus = true;
					m_wallCheck = false;
				}
				else if (m_numbers == 3)
				{
					m_destinationPos.z -= m_point;
					m_destinationPos.x = m_ownerPos.x;
					m_destinationDecision = true;
					m_minus = true;
					m_wallCheck = false;
				}

				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
		}
		else if (m_destinationDecision)
		{
			if (m_numbers % 2 == 0 && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_rightCheck = true;
			}
			else if (m_numbers % 2 == 1 && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_forwardCheck = true;
			}
			if (m_distance >= m_point - 1)
			{
				if (m_rightCheck)
				{
					if (m_ownerPos.x >= m_destinationPos.x - 1 && m_ownerPos.z == m_destinationPos.z && !m_minus)
					{
						m_numbers++;
						m_ownerPos.x = m_destinationPos.x;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						m_rightCheck = false;
					}
					else if (m_ownerPos.x <= m_destinationPos.x + 1 && m_ownerPos.z == m_destinationPos.z && m_minus)
					{
						m_numbers++;
						m_ownerPos.x = m_destinationPos.x;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						if (m_minus)
						{
							m_minus = false;
						}
						m_rightCheck = false;
					}
				}
				if (m_forwardCheck)
				{
					if (m_ownerPos.z >= m_destinationPos.z - 1 && m_ownerPos.x == m_destinationPos.x && !m_minus)
					{
						m_numbers++;
						m_ownerPos.z = m_destinationPos.z;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						m_forwardCheck = false;
					}
					else if (m_ownerPos.z <= m_destinationPos.z + 1 && m_ownerPos.x == m_destinationPos.x && m_minus)
					{
						m_numbers++;
						m_ownerPos.z = m_destinationPos.z;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;

						if (m_minus)
						{
							m_minus = false;
						}
						m_forwardCheck = false;
					}
				}
			}
			if (m_forwardRay.lock()->GetDisObj().size() > 0)
			{
				m_forwardRay.lock()->ResetDisObj();
				m_numbers++;
				m_distance = 0;
				m_time = 0;
				m_moveTime = 0;
				m_wallCheck = true;
				m_destinationDecision = false;

				if (m_forwardCheck)
				{
					m_forwardCheck = false;

				}
				if (m_rightCheck)
				{
					m_rightCheck;
				}
			}

		}

		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			for (auto obj: m_playerRay.lock()->GetDisObj())
			{
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();
				}
			}
		}

		m_trans->SetPosition(m_ownerPos);
		m_trans->SetRotation(m_ownerRot);
		m_Owner->SetAngle(rad + XM_PI * 0.5f);


		float deg = rad * 180 / XM_PI;
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"�ړI�n_x : " << m_destinationPos.x
			<< L"\n�ړI�n_z : " << m_destinationPos.z
			<< L"\n�G�̉�].y : " << m_ownerRot.y
			<< L"\n�G�̉�]�ideg�j" << deg
			<< L"\nright.x" << right.x
			<< L"\nforward.z" << forward.z
			<<L"\n�G��Pos.x : "<<m_ownerPos.x 
			<<L"\n�G��Pos.z : "<< m_ownerPos.z
			<<L"\n�ړ����� : "<<m_distance
			<<L"\n���[�u�^�C�� : "<<m_moveTime
			<<L"\n�ړ��N�[���^�C�� : "<<m_time
			<<L"\n����X : "<< m_numbers
			<<L"\n�� : "<<m_wallCheck 
			<<L"\n�E : "<<m_rightCheck
			<<L"\n�O : "<<m_forwardCheck
			<< endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
