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
		wstringstream wss(L"");
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		auto mapManager= app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<MapManager>(L"MapManager");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		m_playerRay = m_Owner->GetPlayerRay();
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		m_ownerRot.y = rad;//playerの方向に向く
		float deg = rad * 180 / XM_PI;//ラジアンをディグリーに変換（デバック用）


		m_ownerPos.x += -sin(rad) * m_Owner->GetSpeed() * app()->GetElapsedTime();//playerに向かって移動
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

		 

		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		m_Owner->SetAngle(rad + XM_PI * 0.5f);

		//デバックログ
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"プレイヤーPos.x : " << m_playerPos.x
			<< L"\nプレイヤーPos.z : " << m_playerPos.z
			<< L"\n敵の回転.y : " << m_ownerRot.y
			<< L"\n敵の回転（deg）" << deg
			<< L"\n敵のPos.x : " << m_ownerPos.x
			<< L"\n敵のPos.z : " << m_ownerPos.z
			<< L"\na : " << a
			<< endl;
		scene->SetDebugString(wss.str());
	}
//追跡ステートの最後の処理
	void Tracking::OnExit()
	{

	}

	float Tracking::MoveCost()
	{
		return 0;
	}

}
//end basecross
