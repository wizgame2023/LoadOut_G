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
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のPositionを取得

		//Rayの取得
		m_forwardRay = m_Owner->GetForwardRay();//所有者(Enemy)の前方向のRay
		m_playerRay = m_Owner->GetPlayerRay();//所有者(Enemy)からplayerの方向のRay

		m_time += app()->GetElapsedTime();//デルタタイム

		//ベクトルの生成
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));//所有者(Enemy)からplayerの方向の角度
		auto right = m_right * sin(rad);//平行方向のベクトル
		auto forward = m_forward * cos(rad);//垂直方向のベクトル
		m_ownerRot.y = rad;//

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
					m_minus = true;

				}
				else if(m_numbers == 3 )
				{
					m_destinationPos.z -= m_point;
					m_destinationDecision = true;
					m_minus = true;
				}
				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
			if (m_wallCheck)
			{
				if (m_numbers == 0)
				{
					m_destinationPos.x += m_point;
					m_destinationPos.z = m_ownerPos.z;
					m_destinationDecision = true;
					m_wallCheck = false;
				}
				if (m_numbers == 1)
				{
					m_destinationPos.z += m_point;
					m_destinationPos.x = m_ownerPos.x;
					m_destinationDecision = true;
					m_wallCheck = false;
				}
				else if (m_numbers == 2)
				{
					m_destinationPos.x-= m_point;
					m_destinationPos.z = m_ownerPos.z;
					m_destinationDecision = true;
					m_minus = true;
					m_wallCheck = false;
				}
				else if (m_numbers == 3)
				{
					m_destinationPos.z -= m_point;
					m_destinationPos.x = m_ownerPos.x;
					m_destinationDecision = true;
					m_minus = true;
					m_wallCheck = false;
				}

				else if (m_numbers >= 4)
				{
					m_numbers = 0;
				}
			}
		}
		else if (m_destinationDecision)
		{
			if (m_numbers % 2 == 0 && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_rightCheck = true;
			}
			else if (m_numbers % 2 == 1 && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();
				m_forwardCheck = true;
			}
			if (m_distance >= m_point - 1)
			{
				if (m_rightCheck)
				{
					if (m_ownerPos.x >= m_destinationPos.x - 1 && m_ownerPos.z == m_destinationPos.z && !m_minus)
					{
						m_numbers++;
						m_ownerPos.x = m_destinationPos.x;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						m_rightCheck = false;
					}
					else if (m_ownerPos.x <= m_destinationPos.x + 1 && m_ownerPos.z == m_destinationPos.z && m_minus)
					{
						m_numbers++;
						m_ownerPos.x = m_destinationPos.x;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						if (m_minus)
						{
							m_minus = false;
						}
						m_rightCheck = false;
					}
				}
				if (m_forwardCheck)
				{
					if (m_ownerPos.z >= m_destinationPos.z - 1 && m_ownerPos.x == m_destinationPos.x && !m_minus)
					{
						m_numbers++;
						m_ownerPos.z = m_destinationPos.z;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;
						m_forwardCheck = false;
					}
					else if (m_ownerPos.z <= m_destinationPos.z + 1 && m_ownerPos.x == m_destinationPos.x && m_minus)
					{
						m_numbers++;
						m_ownerPos.z = m_destinationPos.z;
						m_distance = 0;
						m_time = 0;
						m_destinationDecision = false;

						if (m_minus)
						{
							m_minus = false;
						}
						m_forwardCheck = false;
					}
				}
			}
			if (m_forwardRay.lock()->GetDisObj().size() > 0)
			{
				m_forwardRay.lock()->ResetDisObj();
				m_numbers++;
				m_distance = 0;
				m_time = 0;
				m_moveTime = 0;
				m_wallCheck = true;
				m_destinationDecision = false;

				if (m_forwardCheck)
				{
					m_forwardCheck = false;

				}
				if (m_rightCheck)
				{
					m_rightCheck;
				}
			}

		}

		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			for (auto obj: m_playerRay.lock()->GetDisObj())
			{
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();
				}
			}
		}

		m_trans->SetPosition(m_ownerPos);
		m_trans->SetRotation(m_ownerRot);
		m_Owner->SetAngle(rad + XM_PI * 0.5f);


		float deg = rad * 180 / XM_PI;
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"目的地_x : " << m_destinationPos.x
			<< L"\n目的地_z : " << m_destinationPos.z
			<< L"\n敵の回転.y : " << m_ownerRot.y
			<< L"\n敵の回転（deg）" << deg
			<< L"\nright.x" << right.x
			<< L"\nforward.z" << forward.z
			<<L"\n敵のPos.x : "<<m_ownerPos.x 
			<<L"\n敵のPos.z : "<< m_ownerPos.z
			<<L"\n移動距離 : "<<m_distance
			<<L"\nムーブタイム : "<<m_moveTime
			<<L"\n移動クールタイム : "<<m_time
			<<L"\n数字X : "<< m_numbers
			<<L"\n壁 : "<<m_wallCheck 
			<<L"\n右 : "<<m_rightCheck
			<<L"\n前 : "<<m_forwardCheck
			<< endl;
		scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
