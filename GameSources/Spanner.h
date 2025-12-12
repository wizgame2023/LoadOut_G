/*!
@file Spanner.h
@brief スパナ(マンホールを打ち上げるためのアイテム)
担当：三瓶裕太
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Spanner :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転

		bool m_updateFlag;//アップデートするかのフラグ

	public:
		Spanner(const shared_ptr<Stage>& stagePtr,const Vec3& pos,const Vec3& rot);
		~Spanner();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;

		void SetUpdateSwitch(bool onOff);
	};


}
//end basecross
