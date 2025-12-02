/*!
@file Hatch.h
@brief ハッチ
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Hatch :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション

		int m_charen;//テクスチャを変えるフラグ
		int m_count;

		float m_time;//時間を測るために必要

	public:
		Hatch(const shared_ptr<Stage>& stagePtr,const Vec3 pos);
		~Hatch();

		void OnCreate()override;
		void OnUpdate()override;
	};


}
//end basecross
