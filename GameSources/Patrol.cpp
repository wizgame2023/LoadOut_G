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
		m_rnd = rand()%2+1;//�����𐶐�
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
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));//���L��(Enemy)����player�̕����̊p�x�v�Z
		auto right = m_right * sin(rad);//���s�����̃x�N�g��
		auto forward = m_forward * cos(rad);//���������̃x�N�g��
		m_ownerRot.y = rad;//�p�x����
	//���񃋁[�g�Z�o
		//���񃋁[�g1(������)
		//������1����������s
		if (m_rnd==1)
		{
			//�ړI�n�����܂��ĂȂ���������s
			if (!m_destinationDecision)
			{
				//�i�ޕ����ɕǂ��Ȃ���������s
				if (!m_wallCheck)
				{
					//�ړI�n�̕���������
					switch (m_numbers)
					{
						//�ړI�n���E�����Ɍ���
					case 0:
						m_destinationPos.x += m_point;
						m_destinationDecision = true;
						break;
						//�ړI�n��������Ɍ���
					case 1:
						m_destinationPos.z += m_point;
						m_destinationDecision = true;
						break;
						//�ړI�n���������Ɍ���
					case 2:
						m_destinationPos.x -= m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//�ړI�n���������Ɍ���
					case 3:
						m_destinationPos.z -= m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//m_numbers��������
					case 4:
						m_numbers = 0;
						break;
					}
				}
				//�i�ޕ����ɕǂ�����������s
				if (m_wallCheck)
				{
					switch (m_numbers)
					{
						//�ړI�n���E�����Ɍ���
					case 0:
						m_destinationPos.x += m_point;
						m_destinationPos.z = m_ownerPos.z;//�ړI�n��z���������L��(Enemy)�ɑ�����
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//�ړI�n��������Ɍ���
					case 1:
						m_destinationPos.z += m_point;
						m_destinationPos.x = m_ownerPos.x;//�ړI�n��x���������L��(Enemy)�ɑ�����
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//�ړI�n���������Ɍ���
					case 2:
						m_destinationPos.x -= m_point;
						m_destinationPos.z = m_ownerPos.z;//�ړI�n��z���������L��(Enemy)�ɑ�����
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//�ړI�n���������Ɍ���
					case 3:
						m_destinationPos.z -= m_point;
						m_destinationPos.x = m_ownerPos.x;//�ړI�n��x���������L��(Enemy)�ɑ�����
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//m_numbers��������
					case 4:
						m_numbers = 0;
						break;
					}
				}
			}
		}
		//���񃋁[�g2(�E���)
		//
		else if(m_rnd==2)
		{
			//�ړI�n�����܂��ĂȂ���������s
			if (!m_destinationDecision)
			{
				//�i�ޕ����ɕǂ��Ȃ���������s
				if (!m_wallCheck)
				{
					//�ړI�n�̕���������
					switch (m_numbers)
					{
						//�ړI�n���������Ɍ���
					case 0:
						m_destinationPos.x -= m_point;
						m_destinationDecision = true;
						break;
						//�ړI�n���������Ɍ���
					case 1:
						m_destinationPos.z -= m_point;
						m_destinationDecision = true;
						break;
						//�ړI�n���E�����Ɍ���
					case 2:
						m_destinationPos.x += m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//�ړI�n��������Ɍ���
					case 3:
						m_destinationPos.z += m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//m_numbers��������
					case 4:
						m_numbers = 0;
						break;
					}
				}
				//�i�ޕ����ɕǂ�����������s
				if (m_wallCheck)
				{
					//�ړI�n�̕���������
					switch (m_numbers)
					{
						//�ړI�n���������Ɍ���
					case 0:
						m_destinationPos.x -= m_point;
						m_destinationPos.z = m_ownerPos.z;
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//�ړI�n���������Ɍ���
					case 1:
						m_destinationPos.z -= m_point;
						m_destinationPos.x = m_ownerPos.x;
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//�ړI�n���E�����Ɍ���
					case 2:
						m_destinationPos.x += m_point;
						m_destinationPos.z = m_ownerPos.z;
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//�ړI�n��������Ɍ���
					case 3:
						m_destinationPos.z += m_point;
						m_destinationPos.x = m_ownerPos.x;
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//m_numbers��������
					case 4:
						m_numbers = 0;
						break;
					}
				}
			}
		}
	//�ړ�����
		//�ړI�n�����܂��Ă�������s
		if (m_destinationDecision)
		{
			//3�b���Ƃ�m_numbers����������������s
			if (m_numbers % 2 == 0 && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();//���s�����Ɉړ�
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();//�ړ��������󂯎��
				m_rightCheck = true;//���s�����Ɉړ����Ă��邱�Ƃ��󂯎��
			}
			//3�b���Ƃ�m_numbers�������������s
			else if (m_numbers % 2 == 1 && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();//���������Ɉړ�
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();//�ړ��������󂯎��
				m_forwardCheck = true;//���������Ɉړ����Ă��邱�Ƃ��󂯎��
			}
			//�ړI�n�̎�O���߂�������s
			if (m_distance >= m_point - 1)
			{
				//���s�����Ɉړ����Ă�����s
				if (m_rightCheck)
				{
					m_rnd = rand() % 2 + 1;//�������ēx�ݒ�
					//���s�����̖ړI�n���̎�O���߂��Ă��Đ����������ړI�n�Ɠ����Ńv���X�����Ɉړ�����������s
					if (m_ownerPos.x >= m_destinationPos.x - 1 && m_ownerPos.z == m_destinationPos.z && !m_minus)
					{
						m_numbers++;//���̖ړI�n�����߂�l�����Z
						m_ownerPos.x = m_destinationPos.x;//���L��(Enemy)�̈ʒu�����̖ړI�n�ɂ���
						m_distance = 0;//�ړ�������������
						m_time = 0;//�ҋ@���Ԃ�������
						m_destinationDecision = false;//�ړI�n�ɂ����߂鏈���Ɉڍs
						m_rightCheck = false;//���s�����̈ړ��̏�����
					}
					//���s�����̖ړI�n���߂��Ă��Đ����������ړI�n�Ɠ����Ń}�C�i�X�����Ɉړ����Ă�������s
					else if (m_ownerPos.x <= m_destinationPos.x + 1 && m_ownerPos.z == m_destinationPos.z && m_minus)
					{
						m_numbers++;//���̖ړI�n�����߂�l�����Z
						m_ownerPos.x = m_destinationPos.x;//���L��(Enemy)�̈ʒu�����̖ړI�n�ɂ���
						m_distance = 0;//�ړ�������������
						m_time = 0;//�ҋ@���Ԃ�������
						m_destinationDecision = false;//�ړI�n�ɂ����߂鏈���Ɉڍs
						m_minus = false;//�}�C�i�X�����̏�����
						m_rightCheck = false;//���s�����̈ړ��̏�����
					}
				}
				//���������Ɉړ����Ă�������s
				if (m_forwardCheck)
				{
					//���������̖ړI�n���̎�O���߂��Ă��ĕ��s�������ړI�n�Ɠ����Ńv���X�����Ɉړ�����������s
					if (m_ownerPos.z >= m_destinationPos.z - 1 && m_ownerPos.x == m_destinationPos.x && !m_minus)
					{
						m_numbers++;//���̖ړI�n�����߂�l�����Z
						m_ownerPos.z = m_destinationPos.z;//���L��(Enemy)�̈ʒu�����̖ړI�n�ɂ���
						m_distance = 0;//�ړ�������������
						m_time = 0;//�ҋ@���Ԃ�������
						m_destinationDecision = false;//�ړI�n�ɂ����߂鏈���Ɉڍs
						m_forwardCheck = false;//���������̈ړ��̏�����
					}
					else if (m_ownerPos.z <= m_destinationPos.z + 1 && m_ownerPos.x == m_destinationPos.x && m_minus)
					{
						m_numbers++;//���̖ړI�n�����߂�l�����Z
						m_ownerPos.z = m_destinationPos.z;//���L��(Enemy)�̈ʒu�����̖ړI�n�ɂ���
						m_distance = 0;//�ړ�������������
						m_time = 0;//�ҋ@���Ԃ�������
						m_destinationDecision = false;//�ړI�n�ɂ����߂鏈���Ɉڍs
						m_minus = false;//�}�C�i�X�����̏�����
						m_forwardCheck = false;//���������̈ړ��̏�����
					}
				}
			}
			//m_forwardRay�����̂ɓ�����������s
			if (m_forwardRay.lock()->GetDisObj().size() > 0)
			{
				m_forwardRay.lock()->ResetDisObj();//Ray�̏�����
				m_rnd = rand() % 2 + 1;//�������ēx�ݒ�
				m_numbers++;//���̖ړI�n�����߂�l�����Z
				m_distance = 0;//�ړ�������������
				m_time = 0;//�ҋ@���Ԃ�������
				m_wallCheck = true;//�ǂ������������Ƃ�Ԃ�
				m_destinationDecision = false;//�ړI�n�ɂ����߂鏈���Ɉڍs

				//���������Ɉړ����Ă�������s
				if (m_forwardCheck)
				{
					m_forwardCheck = false;//���������̈ړ��̏�����

				}
				//���s�����Ɉړ����Ă�����s
				if (m_rightCheck)
				{
					m_rightCheck = false;//���s�����̈ړ��̏�����
				}
			}

		}
		//m_playerRay�����̂ɓ�����������s
		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			//���������I�u�W�F�N�g�̏��擾
			for (auto obj: m_playerRay.lock()->GetDisObj())
			{
				//���������I�u�W�F�N�g���v���C���[����������s
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();//�ǐՃX�e�[�g�Ɉڍs
				}
			}
		}

		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̈ʒu���X�V
		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̊p�x���X�V
		m_Owner->SetAngle(rad + XM_PI * 0.5f);//�����ĕ�������

		////�f�o�b�N�p
		//float deg = rad * 180 / XM_PI;
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"�ړI�n_x : " << m_destinationPos.x
		//	<< L"\n�ړI�n_z : " << m_destinationPos.z
		//	<< L"\n�G�̉�].y : " << m_ownerRot.y
		//	<< L"\n�G�̉�]�ideg�j" << deg
		//	<< L"\nright.x" << right.x
		//	<< L"\nforward.z" << forward.z
		//	<<L"\n�G��Pos.x : "<<m_ownerPos.x 
		//	<<L"\n�G��Pos.z : "<< m_ownerPos.z
		//	<<L"\n�ړ����� : "<<m_distance
		//	<<L"\n���[�u�^�C�� : "<<m_moveTime
		//	<<L"\n�ړ��N�[���^�C�� : "<<m_time
		//	<<L"\n����X : "<< m_numbers
		//	<<L"\n�� : "<<m_wallCheck 
		//	<<L"\n�E : "<<m_rightCheck
		//	<<L"\n�O : "<<m_forwardCheck
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
