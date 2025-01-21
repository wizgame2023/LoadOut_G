/*!
@file RepopEnemy.cpp
@brief 復活した際の敵の処理
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	RepopEnemy::RepopEnemy(const shared_ptr<Enemy> ptrOwner,float goalPosY) :
		StateBase(ptrOwner),
		m_goalPosY(goalPosY),
		m_speed(20.0f)
	{

	}

	RepopEnemy::~RepopEnemy()
	{

	}

	void RepopEnemy::OnStart()
	{
		auto ownerTrans = m_Owner->GetComponent<Transform>();
		auto ownerPos = ownerTrans->GetPosition();
		auto ownerQt = ownerTrans->GetQuaternion();
		float delta = App::GetApp()->GetElapsedTime();

		m_Owner->MoveSwitch(false);//動かないようにする

		//地面に着くまで落下する
		if (ownerPos.y > m_goalPosY)
		{
			ownerPos.y -= m_speed * delta;
			ownerQt = ownerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));		

			//Y座標が目標地点より下に行ったら位置を目標地点に直す
			if (ownerPos.y < m_goalPosY)
			{
				ownerPos.y = m_goalPosY;
				m_Owner->ChangeState<Patrol>();//パトロール状態にする
				m_Owner->MoveSwitch(true);//動けるようにする
			}
		}
			
		ownerTrans->SetQuaternion(ownerQt);
		ownerTrans->SetPosition(ownerPos);//ポジションセット
	}

	void RepopEnemy::OnUpdate()
	{
		auto ownerTrans = m_Owner->GetComponent<Transform>();
		auto ownerPos = ownerTrans->GetPosition();
		auto ownerQt = ownerTrans->GetQuaternion();
		float delta = App::GetApp()->GetElapsedTime();

		//地面に着くまで落下する
		if (ownerPos.y > m_goalPosY)
		{
			ownerPos.y -= m_speed * delta;
			ownerQt = ownerQt * Quat(0.0f, 1.0f * (sin(XMConvertToRadians(30.0f) / 2.0f)), 0.0f, cos(XMConvertToRadians(30.0f) / 2.0f));
			//Y座標が目標地点より下に行ったら位置を目標地点に直す
			if (ownerPos.y < m_goalPosY)
			{
				ownerPos.y = m_goalPosY;
				m_Owner->ChangeState<Patrol>();//パトロール状態にする
				m_Owner->MoveSwitch(true);//動けるようにする
			}
		}

		ownerTrans->SetQuaternion(ownerQt);
		ownerTrans->SetPosition(ownerPos);//ポジションセット

	}

	void RepopEnemy::OnExit()
	{

	}


}
//end basecross
