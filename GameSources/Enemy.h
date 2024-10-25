/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Enemy :public GameObject
	{
	private:
		Vec3 m_pos;
		Vec3 m_rot;
		Vec3 m_scale;

	public:
		Enemy(const shared_ptr<Stage>& StagePtr,
			Vec3& pos,const Vec3& rot,const Vec3& scale);
		//~Enemy();

		virtual void OnCreate() override;
		//virtual void OnUpdate() override;
	};

}
//end basecross
