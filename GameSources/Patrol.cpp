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
	//所有者(Enemy)向きの初期化
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_rot = m_trans->GetRotation();//所有者(Enemy)の回転の取得
		m_rnd = 1;//デバック用 
		//rndが１だった場合、所有者(Enemy)向きを下向き
		if (m_rnd ==1)
		{
			m_rot.y = XM_PI;
		}
		//rndが１以外だった場合、所有者(Enemy)向きを右向き
		else if(m_rnd==2)
		{
			m_rot.y = XM_PI*0.5f;
		}
		m_trans->SetRotation(m_rot);
	}

//巡回ステートの更新処理
	void Patrol::OnUpdate()
	{
	//所有者(Enemy)向きの移動処理
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_time += app()->GetElapsedTime();
		m_pos = m_trans->GetPosition();

		Vec3 forward(0, 0, 1);
		Vec3 fod = forward * m_rot.y;
		//rndが1だった場合、所有者(Enemy)向きが左周りで動く
		if (m_rnd==1)
		{
			if (m_time <= 3)
			{

			}
			//m_pointまで前進する
			if (m_distance <= m_point && m_time > 3)
			{
				m_pos +=  m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance++;
			}
			else if (m_distance > m_point)
			{
				m_rot.y += XM_PI * 0.5f;
				m_distance = 0;
				m_time = 0;
			}
		}
		m_trans->SetPosition(m_pos);
		m_trans->SetRotation(m_rot);
	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
