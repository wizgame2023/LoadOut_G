/*!
@file Character.h
@brief キャラクターなど
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class ClearObject :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		Vec3 m_rot;//回転

	public:
		ClearObject(shared_ptr<Stage>& stagePtr, Vec3 pos, Vec3 rot);
		~ClearObject();

		void OnCreate()override;
		void OnUpdate()override;

		//void OnCollisionEnter(shared_ptr<GameObject>& other)override;
	};




}
//end basecross
