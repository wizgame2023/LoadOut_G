/*!
@file TargetLost.cpp
@brief Player�����������Ƃ��̏���(Tracking��Patrol�Ԃ̏���)
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TargetLost::TargetLost(shared_ptr<Enemy> ptrOwner) :
		Patrol(ptrOwner),
		m_numbers(0),
		m_aStarUpdateCount(0.0f),
		m_arrive(false)
	{
		m_Owner = ptrOwner;
	}

	TargetLost::~TargetLost()
	{

	}

	//�J�n
	void TargetLost::OnStart()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		auto ownerTrans = m_Owner->GetComponent<Transform>();
		m_ownerPos = ownerTrans->GetPosition();//���L��(Enemy)��Position���擾
		auto startPos = m_Owner->GetStartPos();//�����ʒu���擾
		m_ownerRot = ownerTrans->GetRotation();//���L��(Enemy)��Rotation���擾
		m_Owner->SetSpeed(10.0f);//�^�[�Q�b�g���X�g��Ԃ̃X�s�[�h�ɕύX(�p�g���[���Ɠ���)

		//Player�擾
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();


		m_targetPos = MuchPosConvert(startPos);//�ړI�n�����߂�
	
		//AStar���������Ĉړ��o�H���擾
		m_numbers = 0;
		m_navi = RouteSearch(m_ownerPos, m_targetPos);

		//�ړ�����
		m_arrive = MoveActor(m_Owner, m_navi, m_numbers, m_Owner->GetSpeed());

		//Player��T������
		Vision(m_ownerPos, m_playerPos, 8);
	}

	//�X�V
	void TargetLost::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		//Player�擾
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();

		auto ownerTrans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = ownerTrans->GetPosition();//���L��(Enemy)��Position���擾

		m_aStarUpdateCount += delta;
		//AStar�X�V����
		if (m_aStarUpdateCount > 0.3f)
		{
			m_numbers = 0;
			m_navi = RouteSearch(m_ownerPos, m_targetPos);
			m_aStarUpdateCount = 0;
		}

		//�ړ�����
		m_arrive = MoveActor(m_Owner, m_navi, m_numbers, m_Owner->GetSpeed());
	
		//�ړI�n�ɂ��ǂ蒅������X�e�[�g��patrol�ɕύX����
		if (m_arrive)
		{
			m_Owner->ChangeState<Patrol>();
		}

		//Player��T������
		Vision(m_ownerPos, m_playerPos, 8);
	}

	//�I��
	void TargetLost::OnExit()
	{

	}

}
//end basecross
