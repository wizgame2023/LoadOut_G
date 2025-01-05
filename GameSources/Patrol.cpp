/*!
@file Patrol.cpp
@brief 巡回
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//巡回ステートの最初の処理
	void Patrol::OnStart()
	{
		auto mapMgr = m_Owner->GetMapMgr();
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のPositionを取得

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

	//巡回ステートの更新処理
	void Patrol::OnUpdate()
	{
		//CPWallCheck();
		Math math;

		auto AS = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<AStar>(L"AStar");

		//所有者(Enemy)の移動処理
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のPositionを取得
		m_ownerRot = m_trans->GetRotation();

		//Rayの取得
		m_playerRay = m_Owner->GetPlayerRay();//所有者(Enemy)からplayerの方向のRay

		m_time += app()->GetElapsedTime();//デルタタイム

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
		//m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		//m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		//m_Owner->SetAngle(XM_PI * 0.5f);
				//m_playerRayが物体に当たったら実行
		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			//当たったオブジェクトの情報取得
			for (auto obj : m_playerRay.lock()->GetDisObj())
			{
				//当たったオブジェクトがプレイヤーだったら実行
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();//追跡ステートに移行
				}
			}
		}

	}

	void Patrol::OnExit()
	{

	}


}//end basecross

