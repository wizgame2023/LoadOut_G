/*!
@file Tracking.cpp
@brief 追跡
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

//追跡ステートの最初の処理
	void Tracking::OnStart()
	{

	}

//追跡ステートの更新処理
	void Tracking::OnUpdate()
	{
		//playerを追いかける処理
		auto app = App::GetApp;
		Math math;
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		m_playerRay = m_Owner->GetPlayerRay();
		//float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		//m_ownerRot.y = rad;//playerの方向に向く

		auto cost= DirectionCost();
		m_directionRad = cost;

		m_ownerRot.y = m_directionRad;

		m_ownerPos.x += -sin(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//playerに向かって移動
		m_ownerPos.z += -cos(m_directionRad) * m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos.y = 2.5f;

		auto CircleRange= math.GetCircleRange(60, m_ownerPos, m_playerPos);
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
		 auto a = m_directionRad;

		 auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		 Vec3 pos = m_ownerPos;
		 Vec3 playerPos = m_playerPos;
		 auto AStar = mapMgr->GetAStarMap();
		 auto sellPos = mapMgr->ConvertSelMap(pos);
		 auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		m_Owner->SetAngle(m_directionRad + XM_PI * 0.5f);

		float deg = m_directionRad * 180 / XM_PI;//ラジアンをディグリーに変換（デバック用）

		//デバックログ
		auto scene = App::GetApp()->GetScene<Scene>();
		wss /*<< L"プレイヤーPos.x : " << m_playerPos.x
			<< L"\nプレイヤーPos.z : " << m_playerPos.z*/
			<< L"\n敵の回転.y : " << m_ownerRot.y
			<< L"\n敵の回転（deg）" << deg
			<< L"\n敵のPos.x : " << m_ownerPos.x
			<< L"\n敵のPos.z : " << m_ownerPos.z
			<< L"\n右コスト : " << m_costRight
			<< L"\n左コスト : " << m_costLeft
			<< L"\n前コスト : " << m_costFod
			<< L"\n後コスト : " << m_costDown
			<<L"\nAStarPos.x : "<< AStarPos.x
			<< L"\nAStarPos.y : " << AStarPos.y
			<< L"\na : " << a
			<< endl;
		scene->SetDebugString(wss.str());
	}
//追跡ステートの最後の処理
	void Tracking::OnExit()
	{

	}

	float Tracking::DirectionCost()
	{
		Math math;
		auto mapMgr = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		Vec3 pos = m_ownerPos;
		Vec3 playerPos = m_playerPos;
		auto AStar = mapMgr->GetAStarMap();
		auto sellPos = mapMgr->ConvertSelMap(pos);
		auto AStarPos = mapMgr->ConvertAStarMap(sellPos);

		auto rightAStar = AStar[AStarPos.y + 1][AStarPos.x];
		auto leftAStar = AStar[AStarPos.y - 1][AStarPos.x];
		auto fodAStar = AStar[AStarPos.y][AStarPos.x + 1];
		auto downAStar = AStar[AStarPos.y][AStarPos.x - 1];


		auto rightASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x + 2, AStarPos.y));
		auto leftASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x - 2, AStarPos.y));
		auto fodASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y + 2));
		auto downASPos = mapMgr->ConvertA_S(Vec2(AStarPos.x, AStarPos.y - 2));


		auto rightWPos = mapMgr->ConvertWorldMap(rightASPos);
		auto leftWPos = mapMgr->ConvertWorldMap(leftASPos);
		auto fodWPos = mapMgr->ConvertWorldMap(fodASPos);
		auto downWPos = mapMgr->ConvertWorldMap(downASPos);


		auto rightVec = math.GetDistance(rightWPos, playerPos);
		auto liftVec = math.GetDistance(leftWPos, playerPos);
		auto fodVec = math.GetDistance(fodWPos, playerPos);
		auto downVec = math.GetDistance(downWPos, playerPos);


		if (rightAStar == 1)
		{
			m_costRight = 100;
		}
		if (leftAStar == 1)
		{
			m_costLeft = 100;
		}
		if (fodAStar == 1)
		{
			m_costFod = 100;
		}
		if (downAStar == 1)
		{
			m_costDown = 100;
		}
		//if (rightAStar == 0)
		//{
		//	m_costRight = 0;
		//}
		//if (leftAStar == 0)
		//{
		//	m_costLeft = 0;

		//}
		//if (fodAStar == 0)
		//{
		//	m_costFod = 0;
		//}
		//if (downAStar == 0)
		//{
		//	m_costDown = 0;

		//}



		int min_value[] =
		{
			{rightVec + m_costRight},
			{liftVec + m_costLeft},
			{fodVec + m_costFod},
			{downVec + m_costDown},
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
			return math.GetAngle(pos, rightWPos);
		}
		else if (min == min_value[1])
		{
			return math.GetAngle(pos, leftWPos);
		}
		else if (min == min_value[2])
		{
			return math.GetAngle(pos, fodWPos);
		}
		else if (min == min_value[3])
		{
			return math.GetAngle(pos, downWPos);
		}
	}
}
//end basecross
