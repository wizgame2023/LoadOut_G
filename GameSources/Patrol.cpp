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
		
		m_time += app()->GetElapsedTime();

		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));
		auto right = m_right * sin(rad);
		auto forward = m_forward * cos(rad);
		if (!m_destinationDecision)
		{

			if (!m_wallCheck)
			{

				if (m_numbers == 0)
				{
					m_destinationPos.x += m_point;
					m_destinationDecision = true;
				}
				else if (m_numbers == 1)
				{
					m_destinationPos.z += m_point;
					m_destinationDecision = true;

				}
				else if (m_numbers == 2)
				{
					m_destinationPos.x -= m_point;
					m_destinationDecision = true;

				}
				else if(m_numbers == 3 )
				{
					m_destinationPos.z -= m_point;
					m_destinationDecision = true;
				}

				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
			if (m_wallCheck)
			{
				if (m_rightCheck)
				{
					m_destinationPos.x= 0;
					m_destinationPos.z -= m_point;
					m_wallCheck = false;
					m_destinationDecision = true;
					m_forwardCheck = false;
				}
				else if (m_forwardCheck)
				{
					m_destinationPos.z = 0;
					m_destinationPos.x -= m_point;
					m_wallCheck = false;
					m_destinationDecision = true;
					m_forwardCheck = false;

				}
			}

		}
		else if (m_destinationDecision)
		{
			m_ownerRot.y = rad;
			if (m_numbers%2==0  && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_moveTime +=app()->GetElapsedTime();
				m_rightCheck = true;
			}
			else if (m_numbers % 2 == 1 <= m_point && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_moveTime += app()->GetElapsedTime();
				m_forwardCheck=true;
			}
			if (m_moveTime > 5)
			{
				m_numbers++;
				m_time = 0;
				m_moveTime = 0;
				m_destinationDecision = false;

				if ( m_rightCheck)
				{
					m_wallCheck = true;
					m_destinationDecision = false;
				}
				else if (m_forwardCheck)
				{
					m_wallCheck = true;
					m_destinationDecision = false;

				}
			}
		}

		m_trans->SetRotation(m_ownerRot);
		m_trans->SetPosition(m_ownerPos);

		float deg = rad * 180 / XM_PI;

		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"目的地_x : " << m_destinationPos.x
			<< L"\n目的地_z : " << m_destinationPos.z 
			<<L"\n敵の回転.y : "<<m_ownerRot.y 
			<<L"\n敵の回転（deg）"<<deg
			<<L"\n敵のPos.x : "<<m_ownerPos.x 
			<<L"\n敵のPos.z : "<< m_ownerPos.z
			<<L"\n移動距離 : "<<m_distance
			<<L"\n移動クールタイム : "<<m_moveTime
			<<L"\n数字X : "<< m_numbers
			<<L"\n壁 : "<<m_wallCheck << endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
