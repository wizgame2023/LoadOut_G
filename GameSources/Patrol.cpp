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
		auto mapMgr = m_Owner->GetMapMgr();
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾

		//m_checkPoint.clear();
		if (m_checkPoint.size() == 0)
		{
			if (m_ownerPos.z > 0)
			{
				m_cPoint =
				{
					{m_ownerPos},
					{m_ownerPos.x - m_point,m_ownerPos.y,m_ownerPos.z},
					{m_ownerPos.x - m_point,m_ownerPos.y,m_ownerPos.z - m_point},
					{m_ownerPos.x ,m_ownerPos.y,m_ownerPos.z - m_point},

				};
			}
			if (m_ownerPos.z < 0)
			{
				m_cPoint =
				{
					{m_ownerPos},
					{m_ownerPos.x + m_point,m_ownerPos.y,m_ownerPos.z},
					{m_ownerPos.x + m_point,m_ownerPos.y,m_ownerPos.z + m_point},
					{m_ownerPos.x ,m_ownerPos.y,m_ownerPos.z + m_point},

				};

			}
			for (int i = 0; i < 4; i++)
			{
				if (m_cPoint[i].x<mapMgr->GetMapSize() * 0.5 &&
					m_cPoint[i].x>-mapMgr->GetMapSize() * -0.5 &&
					m_cPoint[i].z < mapMgr->GetMapSize() * 0.5 &&
					m_cPoint[i].z > mapMgr->GetMapSize() * -0.5)
				{
					m_checkPoint.push_back(m_cPoint[i]);
				}
				else
				{
					while (m_cPoint[i].x > mapMgr->GetMapSize() * 0.5)
					{
						m_cPoint[i].x -= 10;
					}
					while (m_cPoint[i].x < mapMgr->GetMapSize() * -0.5)
					{
						m_cPoint[i].x += 10;
					}
					while (m_cPoint[i].z > mapMgr->GetMapSize() * 0.5)
					{
						m_cPoint[i].z -= 10;
					}
					while (m_cPoint[i].z < mapMgr->GetMapSize() * -0.5)
					{
						m_cPoint[i].z += 10;
					}
					m_checkPoint.push_back(m_cPoint[i]);

				}
			}
		}
	}

	//����X�e�[�g�̍X�V����
	void Patrol::OnUpdate()
	{
		//CPWallCheck();
		Math math;

		auto AS = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<AStar>(L"AStar");

		//���L��(Enemy)�̈ړ�����
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾
		m_ownerRot = m_trans->GetRotation();

		//Ray�̎擾
		m_playerRay = m_Owner->GetPlayerRay();//���L��(Enemy)����player�̕�����Ray

		m_time += app()->GetElapsedTime();//�f���^�^�C��

		//m_ownerRot.y = rnd;
		if (m_destinationDecision)
		{
			AS->MoveActor(m_Owner, m_navi, m_numbers, m_Owner->GetSpeed());
			if (math.GetDistance(m_ownerPos, m_destinationPos) < 3)
			{
				m_destinationDecision = false;
				m_ownerPos = m_destinationPos;
			}

		}
		if (!m_destinationDecision)
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_ownerPos == m_checkPoint[3])
				{
					m_destinationPos = m_checkPoint[0];
					m_destinationDecision = true;
					break;
				}
				else if (m_ownerPos == m_checkPoint[i])
				{
					m_destinationPos = m_checkPoint[i + 1];
					m_destinationDecision = true;
					break;
				}
			}
			m_numbers = 0;
			m_navi = AS->RouteSearch(m_ownerPos, m_destinationPos);
		}
		//m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		//m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		//m_Owner->SetAngle(XM_PI * 0.5f);
				//m_playerRay�����̂ɓ�����������s
		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			//���������I�u�W�F�N�g�̏��擾
			for (auto obj : m_playerRay.lock()->GetDisObj())
			{
				//���������I�u�W�F�N�g���v���C���[����������s
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();//�ǐՃX�e�[�g�Ɉڍs
				}
			}
		}

	}

	void Patrol::OnExit()
	{

	}


}//end basecross

