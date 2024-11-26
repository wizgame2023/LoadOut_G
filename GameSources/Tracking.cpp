/*!
@file Tracking.cpp
@brief �ǐ�
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//�ǐՃX�e�[�g�̍ŏ��̏���
	void Tracking::OnStart()
	{

	}

//�ǐՃX�e�[�g�̍X�V����
	void Tracking::OnUpdate()
	{
		//player��ǂ������鏈��
		auto app = App::GetApp;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		auto mapManager= app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		m_playerRay = m_Owner->GetPlayerRay();
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		m_ownerRot.y = rad;//player�̕����Ɍ���
		float deg = rad * 180 / XM_PI;//���W�A�����f�B�O���[�ɕϊ��i�f�o�b�N�p�j


		m_ownerPos.x += -sin(rad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//player�Ɍ������Ĉړ�
		m_ownerPos.z+=-cos(rad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos.y = 2.5f;
	
		Math math;
		auto CircleRange= math.GetCircleRange(60, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			m_time += app()->GetElapsedTime();
		}


		if (m_time >= 3)
		{
			m_Owner->ChangeState<Patrol>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		 auto a = CircleRange;

		 

		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		m_Owner->SetAngle(rad + XM_PI * 0.5f);

		//�f�o�b�N���O
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"�v���C���[Pos.x : " << m_playerPos.x
			<< L"\n�v���C���[Pos.z : " << m_playerPos.z
			<< L"\n�G�̉�].y : " << m_ownerRot.y
			<< L"\n�G�̉�]�ideg�j" << deg
			<< L"\n�G��Pos.x : " << m_ownerPos.x
			<< L"\n�G��Pos.z : " << m_ownerPos.z
			<< L"\na : " << a
			<< endl;
		scene->SetDebugString(wss.str());
	}
//�ǐՃX�e�[�g�̍Ō�̏���
	void Tracking::OnExit()
	{

	}

	float Tracking::MoveCost()
	{
		return 0;
	}

}
//end basecross
