/*!
@file Patrol.cpp
@brief ����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{

	//����X�e�[�g�̍ŏ��̏���
	void Patrol::OnStart()
	{
		auto mapMgr = m_Owner->GetMapMgr();
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾
		m_fowanerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾
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
		auto delta = App::GetApp()->GetElapsedTime();
		//CPWallCheck();
		Math math;
		auto AS = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<AStar>(L"AStar");
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");

		//���L��(Enemy)�̈ړ�����
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)��Position���擾
		m_ownerRot = m_trans->GetRotation();

		m_playerPos = player->GetComponent<Transform>()->GetPosition();

		////Ray�̎擾
		//m_playerRay = m_Owner->GetPlayerRay();//���L��(Enemy)����player�̕�����Ray



		m_time += delta;
		if (m_time > 0.3f)
		{
			m_numbers = 0;
			m_navi = AS->RouteSearch(m_ownerPos, m_destinationPos);
			m_time = 0;
		}

		//m_time += app()->GetElapsedTime();//�f���^�^�C��
		Vision(m_ownerPos, m_playerPos, 8);

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
					//���i�ޏꏊ�������Ȃ�X�L�b�v����
					while (m_checkPoint[i] == m_checkPoint[i + 1])
					{
						i++;
						if (i == 3) break;
					}

					m_destinationPos = m_checkPoint[i + 1];
					m_destinationDecision = true;
					break;
				}
			}
			m_numbers = 0;
			m_navi = AS->RouteSearch(m_ownerPos, m_destinationPos);
		}

	}

	void Patrol::OnExit()
	{

	}

	void Patrol::Vision(Vec3 pos, Vec3 target, int vision)
	{
		Vec3 n_pos = pos;
		Vec3 n_fpos = m_fowanerPos;
		Vec3 n_target = target;
		int n_vision = vision;

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		auto angle = m_Owner->GetAngle();

		auto unityMap = mapMgr->GetUnityMap();

		auto sellPos = mapMgr->ConvertSelMap(n_pos);
		auto unityPos = mapMgr->ConvertUnityMap(sellPos);

		auto fsellPos = mapMgr->ConvertSelMap(n_fpos);
		auto funityPos = mapMgr->ConvertUnityMap(fsellPos);

		auto sellTargetPos = mapMgr->ConvertSelMap(n_target);
		auto unityTargetPos = mapMgr->ConvertUnityMap(sellTargetPos);

		for (int i = 1; i < n_vision; i++)
		{
			if (angle == 0)
			{
				//���Z���̏ꍇ
				if ((int)unityPos.y % 2 == 1 && ((int)unityPos.x + i) % 2 == 1)
				{
					if (unityMap[unityPos.y][unityPos.x + i] == 3)
					{
						break;
					}
				}
				//�ǃZ���̏ꍇ
				if((int)unityPos.y % 2 == 1 && ((int)unityPos.x + i) % 2 != 1)
				{
					if (unityMap[unityPos.y][unityPos.x + i] == 1)
					{
						break;
					}
				}
				if (unityPos.x + i == unityTargetPos.x && unityPos.x < unityTargetPos.x && unityPos.y == unityTargetPos.y)
				{
					m_Owner->ChangeState<Tracking>();
				}
						
			}
			if (angle == XM_PI)
			{
				//���Z���̏ꍇ
				if ((int)unityPos.y % 2 == 1 && ((int)unityPos.x - i) % 2)
				{
					if (unityMap[unityPos.y][unityPos.x - i] == 3)
					{
						break;
					}
				}

				//�ǃZ���̏ꍇ
				if ((int)unityPos.y % 2 == 1 && ((int)unityPos.x - i) % 2 != 1)
				{
					if (unityMap[unityPos.y][unityPos.x - i] == 1)
					{
						break;
					}
				}
				if (unityPos.x - i == unityTargetPos.x && unityPos.x > unityTargetPos.x && unityPos.y == unityTargetPos.y)
				{
					m_Owner->ChangeState<Tracking>();
				}
			}
			if (angle == XMConvertToRadians(270))
			{
				//���Z���̏ꍇ
				if (((int)unityPos.y - i) % 2 == 1 && (int)unityPos.x % 2 == 1)
				{
					if (unityMap[unityPos.y - i][unityPos.x] == 3)
					{
						break;
					}
				}

				//�ǃZ���̏ꍇ
				if (((int)unityPos.y - i) % 2 == 0 && (int)unityPos.x % 2 == 1)
				{
					if (unityMap[unityPos.y - i][unityPos.x] == 1)
					{
						break;
					}
				}
				if (unityPos.y - i == unityTargetPos.y && unityPos.y > unityTargetPos.y && unityPos.x == unityTargetPos.x)
				{
					m_Owner->ChangeState<Tracking>();
				}
			}
			if (angle == XM_PI * 0.5)
			{
				//���Z���̏ꍇ
				if (((int)unityPos.y + i) % 2 == 1 && (int)unityPos.x % 2 == 1)
				{
					if (unityMap[unityPos.y + i][unityPos.x] == 3)
					{
						break;
					}
				}

				//�ǃZ���̏ꍇ
				if (((int)unityPos.y + i) % 2 == 0 && (int)unityPos.x % 2 == 1)
				{
					if (unityMap[unityPos.y + i][unityPos.x] == 1)
					{
						break;
					}
				}
				if (unityPos.y + i == unityTargetPos.y && unityPos.y < unityTargetPos.y && unityPos.x == unityTargetPos.x)
				{
					m_Owner->ChangeState<Tracking>();
				}
			}
			

		}

	}
}//end basecross

