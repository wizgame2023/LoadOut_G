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
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//���L��(Enemy)��Transform���擾
		m_ownerPos = m_trans->GetPosition();//���L��(Enemy)�̃|�W�V�������擾
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//player���擾
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//player�̃|�W�V�������擾
		m_playerRay = m_Owner->GetPlayerRay();
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//���L��(Enemy)�𒆐S��player�̕������v�Z
		m_ownerRot.y = rad;//player�̕����Ɍ���

		//auto cost = MoveCost();
		//m_directionRad = math.GetAngle(m_ownerPos,cost);

		//m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(rad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//player�Ɍ������Ĉړ�
		m_ownerPos.z += -cos(rad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos.y = 2.5f;
		
		auto CircleRange = math.GetCircleRange(60, m_ownerPos, m_playerPos);
		if (CircleRange)
		{
			m_time = 0;
		}
		else
		{
			//m_time += app()->GetElapsedTime();
		}


		if (m_time >= 3)
		{
			m_Owner->ChangeState<Patrol>();
		}

		if (m_Owner->GetDistance(m_ownerPos, m_playerPos) < 7)
		{
			m_Owner->ChangeState<Attack>();
		}
		//auto a = m_posVec[m_count-1];

		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto AStar = mapMgr->GetAStarMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		m_trans->SetRotation(m_ownerRot);//���L��(Enemy)�̃��[�e�[�V�����̍X�V
		m_trans->SetPosition(m_ownerPos);//���L��(Enemy)�̃|�W�V�����̍X�V
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//���W�A�����f�B�O���[�ɕϊ��i�f�o�b�N�p�j

		//�f�o�b�N���O
		auto scene = App::GetApp()->GetScene<Scene>();
		wss /*<< L"�v���C���[Pos.x : " << m_playerPos.x
			<< L"\n�v���C���[Pos.z : " << m_playerPos.z*/
			<< L"\n�G�̉�].y : " << m_ownerRot.y
			<< L"\n�G�̉�]�ideg�j" << deg
			<< L"\n�G��Pos.x : " << m_ownerPos.x
			<< L"\n�G��Pos.z : " << m_ownerPos.z
			<< L"\n�E�R�X�g : " << m_costRight
			<< L"\n���R�X�g : " << m_costLeft
			<< L"\n�O�R�X�g : " << m_costFod
			<< L"\n��R�X�g : " << m_costDown
			<< L"\nAStarPos.x : " << AStarPos.x
			<< L"\nAStarPos.y : " << AStarPos.y
			//<< L"\na.x : " << a.x
			//<< L"\na.y : "<<a.y
			//<<L"\na.z : "<<a.z
			<< endl;
		scene->SetDebugString(wss.str());
	}
	//�ǐՃX�e�[�g�̍Ō�̏���
	void Tracking::OnExit()
	{

	}

	Vec3 Tracking::MoveCost()
	{
		Math math;
		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		Vec3 direction;
		auto AStar = mapMgr->GetAStarMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		auto rightAStar = AStar[AStarPos.y][AStarPos.x + 1];
		auto leftAStar = AStar[AStarPos.y][AStarPos.x - 1];
		auto fodAStar = AStar[AStarPos.y - 1][AStarPos.x];
		auto downAStar = AStar[AStarPos.y + 1][AStarPos.x];


		auto rightASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x + 2, AStarPos.y));
		auto leftASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x - 2, AStarPos.y));
		auto fodASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y - 2));
		auto downASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y + 2));


		auto rightWPos = mapMgr->ConvertWorldMap(rightASPos);
		auto leftWPos = mapMgr->ConvertWorldMap(leftASPos);
		auto fodWPos = mapMgr->ConvertWorldMap(fodASPos);
		auto downWPos = mapMgr->ConvertWorldMap(downASPos);


		auto rightVec = math.GetDistance(rightWPos, m_playerPos);
		auto liftVec = math.GetDistance(leftWPos, m_playerPos);
		auto fodVec = math.GetDistance(fodWPos, m_playerPos);
		auto downVec = math.GetDistance(downWPos, m_playerPos);


		if (rightAStar == 1)
		{
			m_costRWall += 1000;
		}
		else if(rightAStar == 0)
		{
			m_costRWall = 0;
		}
		if (leftAStar == 1)
		{
			m_costLWall = 1000;
		}
		else if (leftAStar == 0)
		{
			m_costLWall = 0;
		}
		if (fodAStar == 1)
		{
			m_costFWall += 1000;
		}
		else if (fodAStar == 0)
		{
			m_costFWall = 0;
		}
		if (downAStar == 1)
		{
			m_costDWall += 1000;
		}
		else if (downAStar == 0)
		{
			m_costDWall = 0;
		}



		int min_value[] =
		{
			{rightVec + m_costRight+m_costRWall},
			{liftVec + m_costLeft+m_costLWall},
			{fodVec + m_costFod+m_costFWall},
			{downVec + m_costDown+m_costDWall},
		};
		int min = min_value[0];
		for (int i = 0; i < 4; i++)
		{
			if (min_value[i] < min)
			{
				min = min_value[i];
			}
		}

		if (min == min_value[0])
		{
			direction = rightWPos;
		}
		if (min == min_value[1])
		{
			direction = leftWPos;
		}
		if (min == min_value[2])
		{
			direction = fodWPos;
		}
		if (min == min_value[3])
		{
			direction = downWPos;
		}
		while (direction != m_playerPos)
		{
			if (m_count >= 0)
			{
				//m_posVec[m_count] = direction;
				m_posVec.push_back(direction);

			}

			if (m_count > 0)
			{
				if (playerPos==m_playerPos)
				{
					if (rightWPos == m_posVec[m_count - 1])
					{
						m_costLeft += 100;
						m_costRight = 0;
					}
					if (leftWPos == m_posVec[m_count - 1])
					{
						m_costRight += 100;
						m_costLeft = 0;
					}
					if (fodWPos == m_posVec[m_count - 1])
					{
						m_costDown += 1;
						m_costFod = 0;
					}
					if (downWPos == m_posVec[m_count - 1])
					{
						m_costFod += 1;
						m_costDown = 0;
					}
				}
			}
			if (m_costRight < 0)
			{
				m_costRight = 0;
			}
			if (m_costRight > 100)
			{
				m_costRight = 100;
			}
			if (m_costLeft < 0)
			{
				m_costLeft = 0;
			}
			if (m_costLeft > 100)
			{
				m_costLeft = 100;
			}
			if(m_costFod < 0)
			{
				m_costFod = 0;
			}
			if (m_costFod > 100)
			{
				m_costFod = 100;
			}
			if (m_costDown < 0)
			{
				m_costDown = 0;
			}
			if (m_costDown > 100)
			{
				m_costDown = 100;
			}
			m_count++;
			
			return m_posVec[m_count - 1];
		}

	}

}

//end basecross
