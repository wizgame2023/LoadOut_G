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

	float Actor::GetAngle()
	{
		return m_angle;
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
