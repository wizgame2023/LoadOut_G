/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Battery :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転

	public:
		Battery(shared_ptr<Stage>& stagePtr,Vec3 pos,Vec3 rot);
		~Battery();

		void OnCreate()override;
		void OnUpdate()override;
		void OnDestroy()override;

		void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};


}
//end basecross
