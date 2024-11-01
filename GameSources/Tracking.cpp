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
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		m_ownerRot.y = rad;//player�̕����Ɍ���
		float deg = rad * 180 / XM_PI;//���W�A�����f�B�O���[�ɕϊ��i�f�o�b�N�p�j
		auto speed= -sin(rad)* m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos += speed;//player�Ɍ������Ĉړ�
		
		m_ownerPos.y = 0;
		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		//�f�o�b�N���O
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"�v���C���[Pos.x : " << m_playerPos.x
			<< L"\n�v���C���[Pos.z : " << m_playerPos.z
			<< L"\n�G�̉�].y : " << m_ownerRot.y
			<< L"\n�G�̉�]�ideg�j" << deg
			<< L"\n�G��Pos.x : " << m_ownerPos.x
			<< L"\n�G��Pos.z : " << m_ownerPos.z
			<<L"\n�X�s�[�h : "<<speed << endl;
		scene->SetDebugString(wss.str());

	}

	void Tracking::OnExit()
	{

	}
}
//end basecross
