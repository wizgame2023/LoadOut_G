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
		m_rnd = rand()%2+1;//乱数を生成
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
		float rad = atan2f((m_ownerPos.x - m_destinationPos.x), (m_ownerPos.z - m_destinationPos.z));//所有者(Enemy)からplayerの方向の角度計算
		auto right = m_right * sin(rad);//平行方向のベクトル
		auto forward = m_forward * cos(rad);//垂直方向のベクトル
		m_ownerRot.y = rad;//角度を代入
	//巡回ルート算出
		//巡回ルート1(左周り)
		//乱数が1だったら実行
		if (m_rnd==1)
		{
			//目的地が決まってなかったら実行
			if (!m_destinationDecision)
			{
				//進む方向に壁がなかったら実行
				if (!m_wallCheck)
				{
					//目的地の方向を決定
					switch (m_numbers)
					{
						//目的地を右方向に決定
					case 0:
						m_destinationPos.x += m_point;
						m_destinationDecision = true;
						break;
						//目的地を上方向に決定
					case 1:
						m_destinationPos.z += m_point;
						m_destinationDecision = true;
						break;
						//目的地を左方向に決定
					case 2:
						m_destinationPos.x -= m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//目的地を下方向に決定
					case 3:
						m_destinationPos.z -= m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//m_numbersを初期化
					case 4:
						m_numbers = 0;
						break;
					}
				}
				//進む方向に壁があったら実行
				if (m_wallCheck)
				{
					switch (m_numbers)
					{
						//目的地を右方向に決定
					case 0:
						m_destinationPos.x += m_point;
						m_destinationPos.z = m_ownerPos.z;//目的地のz方向を所有者(Enemy)に揃える
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//目的地を上方向に決定
					case 1:
						m_destinationPos.z += m_point;
						m_destinationPos.x = m_ownerPos.x;//目的地のx方向を所有者(Enemy)に揃える
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//目的地を左方向に決定
					case 2:
						m_destinationPos.x -= m_point;
						m_destinationPos.z = m_ownerPos.z;//目的地のz方向を所有者(Enemy)に揃える
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//目的地を下方向に決定
					case 3:
						m_destinationPos.z -= m_point;
						m_destinationPos.x = m_ownerPos.x;//目的地のx方向を所有者(Enemy)に揃える
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//m_numbersを初期化
					case 4:
						m_numbers = 0;
						break;
					}
				}
			}
		}
		//巡回ルート2(右回り)
		//
		else if(m_rnd==2)
		{
			//目的地が決まってなかったら実行
			if (!m_destinationDecision)
			{
				//進む方向に壁がなかったら実行
				if (!m_wallCheck)
				{
					//目的地の方向を決定
					switch (m_numbers)
					{
						//目的地を左方向に決定
					case 0:
						m_destinationPos.x -= m_point;
						m_destinationDecision = true;
						break;
						//目的地を下方向に決定
					case 1:
						m_destinationPos.z -= m_point;
						m_destinationDecision = true;
						break;
						//目的地を右方向に決定
					case 2:
						m_destinationPos.x += m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//目的地を上方向に決定
					case 3:
						m_destinationPos.z += m_point;
						m_destinationDecision = true;
						m_minus = true;
						break;
						//m_numbersを初期化
					case 4:
						m_numbers = 0;
						break;
					}
				}
				//進む方向に壁があったら実行
				if (m_wallCheck)
				{
					//目的地の方向を決定
					switch (m_numbers)
					{
						//目的地を左方向に決定
					case 0:
						m_destinationPos.x -= m_point;
						m_destinationPos.z = m_ownerPos.z;
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//目的地を下方向に決定
					case 1:
						m_destinationPos.z -= m_point;
						m_destinationPos.x = m_ownerPos.x;
						m_destinationDecision = true;
						m_wallCheck = false;
						break;
						//目的地を右方向に決定
					case 2:
						m_destinationPos.x += m_point;
						m_destinationPos.z = m_ownerPos.z;
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//目的地を上方向に決定
					case 3:
						m_destinationPos.z += m_point;
						m_destinationPos.x = m_ownerPos.x;
						m_destinationDecision = true;
						m_minus = true;
						m_wallCheck = false;
						break;
						//m_numbersを初期化
					case 4:
						m_numbers = 0;
						break;
					}
				}
			}
		}
	//移動処理
		//目的地が決まっていたら実行
		if (m_destinationDecision)
		{
			//3秒ごとにm_numbersが偶数だったら実行
			if (m_numbers % 2 == 0 && m_time >= 3)
			{
				m_ownerPos += -right * m_Owner->GetSpeed() * app()->GetElapsedTime();//平行方向に移動
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();//移動距離を受け取る
				m_rightCheck = true;//平行方向に移動していることを受け取る
			}
			//3秒ごとにm_numbersが奇数だったら実行
			else if (m_numbers % 2 == 1 && m_time >= 3)
			{
				m_ownerPos += -forward * m_Owner->GetSpeed() * app()->GetElapsedTime();//垂直方向に移動
				m_distance += m_Owner->GetSpeed() * app()->GetElapsedTime();//移動距離を受け取る
				m_forwardCheck = true;//水平方向に移動していることを受け取る
			}
			//目的地の手前を過ぎたら実行
			if (m_distance >= m_point - 1)
			{
				//平行方向に移動してたら実行
				if (m_rightCheck)
				{
					m_rnd = rand() % 2 + 1;//乱数を再度設定
					//平行方向の目的地をの手前を過ぎていて垂直方向が目的地と同じでプラス方向に移動しいたら実行
					if (m_ownerPos.x >= m_destinationPos.x - 1 && m_ownerPos.z == m_destinationPos.z && !m_minus)
					{
						m_numbers++;//次の目的地を決める値を加算
						m_ownerPos.x = m_destinationPos.x;//所有者(Enemy)の位置を今の目的地にする
						m_distance = 0;//移動距離を初期化
						m_time = 0;//待機時間を初期化
						m_destinationDecision = false;//目的地にを決める処理に移行
						m_rightCheck = false;//平行方向の移動の初期化
					}
					//平行方向の目的地を過ぎていて垂直方向が目的地と同じでマイナス方向に移動していたら実行
					else if (m_ownerPos.x <= m_destinationPos.x + 1 && m_ownerPos.z == m_destinationPos.z && m_minus)
					{
						m_numbers++;//次の目的地を決める値を加算
						m_ownerPos.x = m_destinationPos.x;//所有者(Enemy)の位置を今の目的地にする
						m_distance = 0;//移動距離を初期化
						m_time = 0;//待機時間を初期化
						m_destinationDecision = false;//目的地にを決める処理に移行
						m_minus = false;//マイナス方向の初期化
						m_rightCheck = false;//平行方向の移動の初期化
					}
				}
				//垂直方向に移動していたら実行
				if (m_forwardCheck)
				{
					//垂直方向の目的地をの手前を過ぎていて平行方向が目的地と同じでプラス方向に移動しいたら実行
					if (m_ownerPos.z >= m_destinationPos.z - 1 && m_ownerPos.x == m_destinationPos.x && !m_minus)
					{
						m_numbers++;//次の目的地を決める値を加算
						m_ownerPos.z = m_destinationPos.z;//所有者(Enemy)の位置を今の目的地にする
						m_distance = 0;//移動距離を初期化
						m_time = 0;//待機時間を初期化
						m_destinationDecision = false;//目的地にを決める処理に移行
						m_forwardCheck = false;//垂直方向の移動の初期化
					}
					else if (m_ownerPos.z <= m_destinationPos.z + 1 && m_ownerPos.x == m_destinationPos.x && m_minus)
					{
						m_numbers++;//次の目的地を決める値を加算
						m_ownerPos.z = m_destinationPos.z;//所有者(Enemy)の位置を今の目的地にする
						m_distance = 0;//移動距離を初期化
						m_time = 0;//待機時間を初期化
						m_destinationDecision = false;//目的地にを決める処理に移行
						m_minus = false;//マイナス方向の初期化
						m_forwardCheck = false;//垂直方向の移動の初期化
					}
				}
			}
			//m_forwardRayが物体に当たったら実行
			if (m_forwardRay.lock()->GetDisObj().size() > 0)
			{
				m_forwardRay.lock()->ResetDisObj();//Rayの初期化
				m_rnd = rand() % 2 + 1;//乱数を再度設定
				m_numbers++;//次の目的地を決める値を加算
				m_distance = 0;//移動距離を初期化
				m_time = 0;//待機時間を初期化
				m_wallCheck = true;//壁が当たったことを返す
				m_destinationDecision = false;//目的地にを決める処理に移行

				//垂直方向に移動していたら実行
				if (m_forwardCheck)
				{
					m_forwardCheck = false;//垂直方向の移動の初期化

				}
				//平行方向に移動してたら実行
				if (m_rightCheck)
				{
					m_rightCheck = false;//平行方向の移動の初期化
				}
			}

		}
		//m_playerRayが物体に当たったら実行
		if (m_playerRay.lock()->GetDisObj().size() > 0)
		{
			//当たったオブジェクトの情報取得
			for (auto obj: m_playerRay.lock()->GetDisObj())
			{
				//当たったオブジェクトがプレイヤーだったら実行
				if (obj.lock()->FindTag(L"Player"))
				{
					m_Owner->ChangeState<Tracking>();//追跡ステートに移行
				}
			}
		}

		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)の位置を更新
		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)の角度を更新
		m_Owner->SetAngle(rad + XM_PI * 0.5f);//向いて方向を代入

		////デバック用
		//float deg = rad * 180 / XM_PI;
		//wstringstream wss(L"");
		//auto scene = App::GetApp()->GetScene<Scene>();
		//wss << L"目的地_x : " << m_destinationPos.x
		//	<< L"\n目的地_z : " << m_destinationPos.z
		//	<< L"\n敵の回転.y : " << m_ownerRot.y
		//	<< L"\n敵の回転（deg）" << deg
		//	<< L"\nright.x" << right.x
		//	<< L"\nforward.z" << forward.z
		//	<<L"\n敵のPos.x : "<<m_ownerPos.x 
		//	<<L"\n敵のPos.z : "<< m_ownerPos.z
		//	<<L"\n移動距離 : "<<m_distance
		//	<<L"\nムーブタイム : "<<m_moveTime
		//	<<L"\n移動クールタイム : "<<m_time
		//	<<L"\n数字X : "<< m_numbers
		//	<<L"\n壁 : "<<m_wallCheck 
		//	<<L"\n右 : "<<m_rightCheck
		//	<<L"\n前 : "<<m_forwardCheck
		//	<< endl;
		//scene->SetDebugString(wss.str());

	}

	void Patrol::OnExit()
	{

	}

}
//end basecross
