/*!
@file Manhole.h
@brief マンホール
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	class Manhole :public GameObject
	{
	private:
		Vec3 m_pos;//ポジション
		weak_ptr<MapManager> m_mapManager;//マップマネージャー

	public:
		Manhole(shared_ptr<Stage>& stagePtr,Vec3 pos);
		~Manhole();

		void OnCreate()override;
		void OnUpdate()override;
	};

}
//end basecross
