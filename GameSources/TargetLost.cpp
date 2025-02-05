/*!
@file TargetLost.cpp
@brief Playerを見失ったときの処理(Tracking→Patrol間の処理)
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	TargetLost::TargetLost(shared_ptr<Enemy> ptrOwner) :
		Patrol(ptrOwner),
		m_numbers(0),
		m_aStarUpdateCount(0.0f),
		m_arrive(false)
	{
		m_Owner = ptrOwner;
	}

	TargetLost::~TargetLost()
	{

	}

	//開始
	void TargetLost::OnStart()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		auto ownerTrans = m_Owner->GetComponent<Transform>();
		m_ownerPos = ownerTrans->GetPosition();//所有者(Enemy)のPositionを取得
		auto startPos = m_Owner->GetStartPos();//初期位置を取得
		m_ownerRot = ownerTrans->GetRotation();//所有者(Enemy)のRotationを取得
		m_Owner->SetSpeed(10.0f);//ターゲットロスト状態のスピードに変更(パトロールと同じ)

		//Player取得
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();


		m_targetPos = MuchPosConvert(startPos);//目的地を決める
	
		//AStar処理をして移動経路を取得
		m_numbers = 0;
		m_navi = RouteSearch(m_ownerPos, m_targetPos);

		//移動処理
		m_arrive = MoveActor(m_Owner, m_navi, m_numbers, m_Owner->GetSpeed());

		//Playerを探す処理
		Vision(m_ownerPos, m_playerPos, 8);
	}

	//更新
	void TargetLost::OnUpdate()
	{
		auto delta = App::GetApp()->GetElapsedTime();

		//Player取得
		auto player = App::GetApp()->GetScene<Scene>()->GetActiveStage()->GetSharedGameObject<Player>(L"Player");
		m_playerPos = player->GetComponent<Transform>()->GetPosition();

		auto ownerTrans = m_Owner->GetComponent<Transform>();//所有者(Enemy)のTransformを取得
		m_ownerPos = ownerTrans->GetPosition();//所有者(Enemy)のPositionを取得

		m_aStarUpdateCount += delta;
		//AStar更新処理
		if (m_aStarUpdateCount > 0.3f)
		{
			m_numbers = 0;
			m_navi = RouteSearch(m_ownerPos, m_targetPos);
			m_aStarUpdateCount = 0;
		}

		//移動処理
		m_arrive = MoveActor(m_Owner, m_navi, m_numbers, m_Owner->GetSpeed());
	
		//目的地にたどり着いたらステートをpatrolに変更する
		if (m_arrive)
		{
			m_Owner->ChangeState<Patrol>();
		}

		//Playerを探す処理
		Vision(m_ownerPos, m_playerPos, 8);
	}

	//終了
	void TargetLost::OnExit()
	{

	}

}
//end basecross
