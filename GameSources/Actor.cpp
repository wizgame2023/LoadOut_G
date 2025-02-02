/*!
@file Actor.cpp
@brief PlayerやEnemyなど動くオブジェクトの親クラス
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	Actor::Actor(shared_ptr<Stage>& stagePtr):
		GameObject(stagePtr)
	{

	}

	Actor::~Actor()
	{

	}

	void Actor::OnUpdate()
	{
		auto pos = GetComponent<Transform>()->GetPosition();//ポジション取得
		auto mapManager = GetStage()->GetSharedGameObject<MapManager>(L"MapManager");//マップマネージャー取得
		Vec2 selPos = mapManager->ConvertSelMap(pos);//今いるセル座標を取得
		int selNow = mapManager->SelMapNow(pos);//現在いるセル座標に何があるかを取得

		//確認したセル座標が前より違っていたら
		if (selPos != m_selPosNow)
		{
			//今いるセル座標を変更して前いるセル座標を保存する
			m_selPosBefor = m_selPosNow;
			m_selPosNow = selPos;
		}
	}

	float Actor::GetAngle()
	{
		return m_angle;
	}

	//現在のセル座標のゲッター
	Vec2 Actor::GetSelPosNow()
	{
		return m_selPosNow;
	}

	//前いたセル座標のゲッター
	Vec2 Actor::GetSelPosBefor()
	{
		return m_selPosBefor;
	}


	void Actor::SetAngle(float angle)
	{
		m_angle = angle;
	}

	void Actor::MoveSwitch(bool onoff)
	{
		m_move = onoff;
	}


}
//end basecross
