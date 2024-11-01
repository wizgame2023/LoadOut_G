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
		m_trans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = m_trans->GetPosition();//所有者(Enemy)のポジションを取得
		auto player = app()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");//playerを取得
		m_playerPos = player->GetComponent<Transform>()->GetPosition();//playerのポジションを取得
		float rad = atan2f((m_ownerPos.x - m_playerPos.x), (m_ownerPos.z - m_playerPos.z));//所有者(Enemy)を中心にplayerの方向を計算
		m_ownerRot.y = rad;//playerの方向に向く
		float deg = rad * 180 / XM_PI;//ラジアンをディグリーに変換（デバック用）
		auto speed= -sin(rad)* m_Owner->GetSpeed() * app()->GetElapsedTime();
		m_ownerPos += speed;//playerに向かって移動
		
		m_ownerPos.y = 0;
		m_trans->SetRotation(m_ownerRot);//所有者(Enemy)のローテーションの更新
		m_trans->SetPosition(m_ownerPos);//所有者(Enemy)のポジションの更新
		//デバックログ
		wstringstream wss(L"");
		auto scene = App::GetApp()->GetScene<Scene>();
		wss << L"プレイヤーPos.x : " << m_playerPos.x
			<< L"\nプレイヤーPos.z : " << m_playerPos.z
			<< L"\n敵の回転.y : " << m_ownerRot.y
			<< L"\n敵の回転（deg）" << deg
			<< L"\n敵のPos.x : " << m_ownerPos.x
			<< L"\n敵のPos.z : " << m_ownerPos.z
			<<L"\nスピード : "<<speed << endl;
		scene->SetDebugString(wss.str());

	}

	void Tracking::OnExit()
	{

	}
}
//end basecross
