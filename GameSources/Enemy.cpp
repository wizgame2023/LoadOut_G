/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"
#include "Enemy.h"

namespace basecross {
	Enemy::Enemy(const shared_ptr<Stage>& StagePtr,
		Vec3& pos, const Vec3& rot, const Vec3& scale) :
		GameObject(StagePtr),
		m_pos(pos),
		m_rot(rot),
		m_scale(scale)
	{
	}

	void Enemy::OnCreate()
	{
		auto trans = GetComponent<Transform>();
		trans->SetPosition(m_pos);
		trans->SetRotation(m_rot);
		trans->SetScale(m_scale);

		auto ptrDraw = AddComponent<PNTStaticDraw>();
		ptrDraw->SetMeshResource(L"DEFAULT_CUBE");

	}

}
//end basecross
