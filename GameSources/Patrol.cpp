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

	}

//巡回ステートの更新処理
	void Patrol::OnUpdate()
	{
	//所有者(Enemy)の移動処理
		auto app = App::GetApp;
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));
		m_ownerRot.y = rad;
		float deg = rad * 180 / XM_PI;

		auto right = m_right * sin(rad);
		auto forward = m_forward * sin(rad);

		if (!m_destinationDecision)
		{
			if (m_rnd==1)
			{
				if (m_ownerPos.x<=m_ownerPos.z)
				{
					m_destinationPos.x += m_point;
					m_destinationDecision = true;
				}
			}
		}
		else if (m_destinationDecision)
		{
			m_time += app()->GetElapsedTime();
			if (m_destinationPos.x > m_destinationPos.z && m_distance <= m_point)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance +=m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			else if (m_destinationPos.x < m_destinationPos.z && m_distance <= m_point)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
			}
			if(m_ownerPos==m_destinationPos)
			{
				m_destinationDecision = false;
				m_distance = 0;
			}
		}

		m_trans->SetRotation(m_ownerRot);
		m_trans->SetPosition(m_ownerPos);


		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"目的地_x : " << m_destinationPos.x
			<< L"\n目的地_z : " << m_destinationPos.z 
			<<L"\n敵の回転.y : "<<m_ownerRot.y 
			<<L"\n敵の回転（deg）"<<deg
			<<L"\n敵のPos.x : "<<m_ownerPos.x 
			<<L"\n敵のPos.z : "<< m_ownerPos.z
			<<L"\n移動距離 : "<<m_distance << endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
